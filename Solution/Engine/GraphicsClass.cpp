////////////////////////////////////////////////////////////////////////////////
// Filename: GraphicsClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "GraphicsClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_TextureShader = 0;
	m_Map = 0;
	m_Text = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialise(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialise the Direct3D object.
	result = m_D3D->Initialise(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}
	m_Camera->SetScreenSize(screenWidth, screenHeight);

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	m_Text = new TextClass();
	if(!m_Text)
	{
		return false;
	}
	result = m_Text->Initialise(m_D3D->GetDevice(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the text object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialise the texture shader object.
	result = m_TextureShader->Initialise(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialise the map
	m_Map = new MapClass;
	if(!m_Map)
	{
		return false;
	}
	result = m_Map->Initialise(m_D3D->GetDevice(), L"./maps/BigMaze.txt", m_TextureShader);
	if(!result)
	{
		return false;
	}
	
	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the map object.
	if(m_Map)
	{
		m_Map->Shutdown();
		delete m_Map;
		m_Map = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(int mouseX, int mouseY, int fps)
{
	bool result;

	// Convert screen coords to tile coords
	// xy goes from 0 to 1
	float x = (float)mouseX / 800;
	float y = (float)mouseY / 600;

	float tX = (float)800 / 32; // = 25.00
	float tY = (float)600 / 32; // = 18.75

	int tileX = x * tX;
	int tileY = y * tY;

	// Update the stats
	result = m_Text->SetFps(fps);
	//result = m_Text->SetMousePosition(mouseX, mouseY);
	result = m_Text->SetMousePosition((int)(x*100), tileY);

	m_Map->Frame(m_Camera->GetScreenWidth(), m_Camera->GetScreenHeight(), mouseX, mouseY);

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Map->Render(m_D3D->GetDevice(), worldMatrix, viewMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	m_Text->Render(m_D3D->GetDevice(), worldMatrix, orthoMatrix);

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


