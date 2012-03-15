#pragma once
class CTile
{
public:
	CTile(void);
	~CTile(void);

	int tileId;
	int x;
	int y;

	void onRender(GLuint texture);
};

