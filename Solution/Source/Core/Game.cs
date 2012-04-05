using System;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using SharpDX.Windows;

using Buffer = SharpDX.Direct3D10.Buffer;
using Device = SharpDX.Direct3D10.Device;
using DriverType = SharpDX.Direct3D10.DriverType;
using System.Diagnostics;
using System.Windows.Forms;


namespace Core
{
    public class Game : IDisposable
    {
        private CoreManager m_Game;
        private RenderForm m_RenderForm;
        private Device m_Device;
        private SwapChain m_SwapChain;
        private Stopwatch m_Clock;
        private Device m_Context;
        private RenderTargetView m_RenderView;
        private DepthStencilView m_DepthView;
        private Buffer m_ConstantBuffer;
        private Matrix m_ViewProj;
        private InputLayout m_InputLayout;
        private PixelShader m_PixelShader;
        private VertexShader m_VertexShader;
        private GeometryShader m_SpriteShader;
        private ShaderResourceView m_SpriteTex;

        bool EscapePressed = false;

        
        private void OnRenderFormResize(object sender, EventArgs e)
        {
            ResizeScreen();
        }

        
        private void OnKeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                EscapePressed = true;
            }
        }


        public void Initialise()
        {
            m_Clock = new Stopwatch();
            m_Clock.Start();

            m_Game = new CoreManager();
            m_Game.Initialise();

            m_RenderForm = new RenderForm("Core Renderer Form");
            m_RenderForm.Resize += new EventHandler(OnRenderFormResize);
            m_RenderForm.KeyUp += new KeyEventHandler(OnKeyUp);

            CreateSwapChainAndDevice();
            ResizeScreen();

            // Ignore all Windows events
            var factory = m_SwapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(m_RenderForm.Handle, WindowAssociationFlags.IgnoreAll);

            // Compile the shaders
            ShaderBytecode vertexShaderByteCode = ShaderBytecode.CompileFromFile("./shaders/MiniCube.fx", "VS", "vs_4_0", ShaderFlags.None, EffectFlags.None);
            vertexShaderByteCode.Save("./shaders/MiniCube_VS.fxo");
            m_VertexShader = new VertexShader(m_Device, vertexShaderByteCode);

            ShaderBytecode pixelShaderByteCode = ShaderBytecode.CompileFromFile("./shaders/MiniCube.fx", "PS", "ps_4_0", ShaderFlags.None, EffectFlags.None);
            pixelShaderByteCode.Save("./shaders/MiniCube_PS.fxo");
            m_PixelShader = new PixelShader(m_Device, pixelShaderByteCode);

            ShaderBytecode geometryShaderByteCode = ShaderBytecode.CompileFromFile("./shaders/sprite.fx", "GS", "gs_4_0", ShaderFlags.None, EffectFlags.None);
            geometryShaderByteCode.Save("./shaders/sprite.fxo");
            m_SpriteShader = new GeometryShader(m_Device, geometryShaderByteCode);

            // Load the Sprite tile texture
            m_SpriteTex = ShaderResourceView.FromFile(m_Device, "./textures/tiles.png");
            


            // Layout
            m_InputLayout = new InputLayout(m_Device, ShaderSignature.GetInputSignature(vertexShaderByteCode), new[]
            {
                new InputElement("POSITION", 0, Format.R32G32B32A32_Float, 0, 0),
                new InputElement("COLOR", 0, Format.R32G32B32A32_Float, 16, 0)
            });


            m_ConstantBuffer = new Buffer(
                m_Device, 
                Utilities.SizeOf<Matrix>(),
                ResourceUsage.Default,
                BindFlags.ConstantBuffer,
                CpuAccessFlags.None,
                ResourceOptionFlags.None
            );

             // Cleanup
            vertexShaderByteCode.Dispose();
            pixelShaderByteCode.Dispose();
            factory.Dispose();

        }


        private void CreateSwapChainAndDevice()
        {
            // Setup the Swap Chain description
            var desc = new SwapChainDescription()
            {
                BufferCount = 1,
                ModeDescription = new ModeDescription(m_RenderForm.ClientSize.Width, m_RenderForm.ClientSize.Height, new Rational(60, 1), Format.R8G8B8A8_UNorm),
                IsWindowed = true,
                OutputHandle = m_RenderForm.Handle,
                SampleDescription = new SampleDescription(1, 0),
                SwapEffect = SwapEffect.Discard,
                Usage = Usage.RenderTargetOutput
            };

            // Create the device, and the swap chain
            Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, desc, out m_Device, out m_SwapChain);
            m_Context = m_Device;
        }


        private void ResizeScreen()
        {
            if (m_RenderView != null)
            {
                m_RenderView.Dispose();
            }

            m_SwapChain.ResizeBuffers(
                2,
                m_RenderForm.ClientSize.Width, m_RenderForm.ClientSize.Height,
                Format.R8G8B8A8_UNorm,
                (int)SwapChainFlags.AllowModeSwitch
            );

            // Create new render target view
            var backBuffer = Texture2D.FromSwapChain<Texture2D>(m_SwapChain, 0);
            m_RenderView = new RenderTargetView(m_Device, backBuffer);
            backBuffer.Dispose();

            // Create the viewport
            m_Context.Rasterizer.SetViewports(new Viewport(0, 0, m_RenderForm.ClientSize.Width, m_RenderForm.ClientSize.Height, 0.0f, 1.0f));

            // Create the depth buffer and view
            var depthBuffer = new Texture2D(m_Device, new Texture2DDescription()
            {
                Format = Format.D32_Float_S8X24_UInt,
                ArraySize = 1,
                MipLevels = 1,
                Width = m_RenderForm.ClientSize.Width,
                Height = m_RenderForm.ClientSize.Height,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.DepthStencil,
                CpuAccessFlags = CpuAccessFlags.None,
                OptionFlags = ResourceOptionFlags.None
            });
            m_DepthView = new DepthStencilView(m_Device, depthBuffer);

            // prepare the matrices
            var view = Matrix.LookAtLH(new Vector3(0, 0, -5), new Vector3(0, 0, 0), Vector3.UnitY);
            var proj = Matrix.PerspectiveFovLH((float)Math.PI / 4.0f, m_RenderForm.ClientSize.Width / (float)m_RenderForm.ClientSize.Height, 0.1f, 100.0f);
            m_ViewProj = Matrix.Multiply(view, proj);
        }


        public void Run()
        {
            // Main loop!
            RenderLoop.Run(m_RenderForm, () =>
            {
                var time = m_Clock.ElapsedMilliseconds / 1000.0f;

                if (EscapePressed == true)
                {
                    m_RenderForm.Close();
                }

                // Clear views
                m_Context.OutputMerger.SetTargets(m_DepthView, m_RenderView);

                m_Context.ClearDepthStencilView(m_DepthView, DepthStencilClearFlags.Depth, 1.0f, 0);
                m_Context.ClearRenderTargetView(m_RenderView, Colors.Black);

                // Update WorldViewProj Matrix
                var WorldViewProj = Matrix.RotationX(time) * Matrix.RotationY(time * 2) * Matrix.RotationZ(time * 0.7f) * m_ViewProj;
                WorldViewProj.Transpose();
                m_Context.UpdateSubresource(ref WorldViewProj, m_ConstantBuffer);

                // Draw the cube
                // Instantiate a new buffer of verts
                var vertices = Buffer.Create(m_Device, BindFlags.VertexBuffer, new[]
                                      {
                                          new Vector4(-1.0f, -1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Front
                                          new Vector4(-1.0f,  1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f),
                                          new Vector4( 1.0f,  1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f),
                                          new Vector4(-1.0f, -1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f),
                                          new Vector4( 1.0f,  1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f),
                                          new Vector4( 1.0f, -1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f),

                                          new Vector4(-1.0f, -1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f), // BACK
                                          new Vector4( 1.0f,  1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f),
                                          new Vector4(-1.0f,  1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f),
                                          new Vector4(-1.0f, -1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f),
                                          new Vector4( 1.0f, -1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f),
                                          new Vector4( 1.0f,  1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f),

                                          new Vector4(-1.0f, 1.0f, -1.0f,  1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f), // Top
                                          new Vector4(-1.0f, 1.0f,  1.0f,  1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f),
                                          new Vector4( 1.0f, 1.0f,  1.0f,  1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f),
                                          new Vector4(-1.0f, 1.0f, -1.0f,  1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f),
                                          new Vector4( 1.0f, 1.0f,  1.0f,  1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f),
                                          new Vector4( 1.0f, 1.0f, -1.0f,  1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f),

                                          new Vector4(-1.0f,-1.0f, -1.0f,  1.0f), new Vector4(1.0f, 1.0f, 0.0f, 1.0f), // Bottom
                                          new Vector4( 1.0f,-1.0f,  1.0f,  1.0f), new Vector4(1.0f, 1.0f, 0.0f, 1.0f),
                                          new Vector4(-1.0f,-1.0f,  1.0f,  1.0f), new Vector4(1.0f, 1.0f, 0.0f, 1.0f),
                                          new Vector4(-1.0f,-1.0f, -1.0f,  1.0f), new Vector4(1.0f, 1.0f, 0.0f, 1.0f),
                                          new Vector4( 1.0f,-1.0f, -1.0f,  1.0f), new Vector4(1.0f, 1.0f, 0.0f, 1.0f),
                                          new Vector4( 1.0f,-1.0f,  1.0f,  1.0f), new Vector4(1.0f, 1.0f, 0.0f, 1.0f),

                                          new Vector4(-1.0f, -1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 1.0f, 1.0f), // Left
                                          new Vector4(-1.0f, -1.0f,  1.0f, 1.0f), new Vector4(1.0f, 0.0f, 1.0f, 1.0f),
                                          new Vector4(-1.0f,  1.0f,  1.0f, 1.0f), new Vector4(1.0f, 0.0f, 1.0f, 1.0f),
                                          new Vector4(-1.0f, -1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 1.0f, 1.0f),
                                          new Vector4(-1.0f,  1.0f,  1.0f, 1.0f), new Vector4(1.0f, 0.0f, 1.0f, 1.0f),
                                          new Vector4(-1.0f,  1.0f, -1.0f, 1.0f), new Vector4(1.0f, 0.0f, 1.0f, 1.0f),

                                          new Vector4( 1.0f, -1.0f, -1.0f, 1.0f), new Vector4(0.0f, 1.0f, 1.0f, 1.0f), // Right
                                          new Vector4( 1.0f,  1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 1.0f, 1.0f),
                                          new Vector4( 1.0f, -1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 1.0f, 1.0f),
                                          new Vector4( 1.0f, -1.0f, -1.0f, 1.0f), new Vector4(0.0f, 1.0f, 1.0f, 1.0f),
                                          new Vector4( 1.0f,  1.0f, -1.0f, 1.0f), new Vector4(0.0f, 1.0f, 1.0f, 1.0f),
                                          new Vector4( 1.0f,  1.0f,  1.0f, 1.0f), new Vector4(0.0f, 1.0f, 1.0f, 1.0f),
                                });
                m_Context.InputAssembler.InputLayout = m_InputLayout;
                m_Context.InputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleList;
                m_Context.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertices, Utilities.SizeOf<Vector4>() * 2, 0));
                m_Context.VertexShader.SetConstantBuffer(0, m_ConstantBuffer);
                m_Context.VertexShader.Set(m_VertexShader);
                m_Context.PixelShader.Set(m_PixelShader);
                m_Context.PixelShader.SetShaderResource(0, m_SpriteTex);

                m_Context.Draw(36, 0);

                m_Game.Update();
                m_Game.Render();

                // Present!
                m_SwapChain.Present(0, PresentFlags.None);

            });

        }

        public void RenderSprites()
        {

        }


        public void Dispose()
        {
            m_Game.Dispose();
            m_VertexShader.Dispose();
            m_PixelShader.Dispose();
            m_InputLayout.Dispose();
            m_RenderView.Dispose();
            m_Context.ClearState();
            m_Context.Flush();
            m_Device.Dispose();
            m_Context.Dispose();
            m_SwapChain.Dispose();
        }
    }
}
