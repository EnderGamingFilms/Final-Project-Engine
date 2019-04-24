#include "Init.h"


Ship::Ship(float turnSpeed, float movementSpeed, unsigned int bodyColor, unsigned int rivetColor)
{
	bool map[4][4] =
	{
		{false, true, true, true},
		{ false, true, true, true },
		{ false, true, true, true },
		{ false, true, true, true }
	};

	gameBound.Init(1, true, 0.005);

	this->turnSpeed = turnSpeed;
	this->movementSpeed = movementSpeed;

	body.Init(0.175, 0.19, 0.19);
	body.TranslateToOrigin();

	hb.Init(0.15);

	leftRivet.Init(0.045, 0.032);
	leftRivet.Translate(-0.04, -0.04);

	rightRivet.Init(0.045, 0.032);
	rightRivet.Translate(0.04, -0.04);

	thruster.Init(0.04);
	thruster.Translate(0, -0.05);


	this->Rotate(1.57);

	this->FreeRotate(-1.59);


	this->isAlloced = true;
	this->bodyColor = bodyColor;
	this->rivetColor = rivetColor;

}


void Ship::Draw()
{
	if (isAlloced)
	{

		glUseProgram(rivetColor);

		thruster.Draw();

		glUseProgram(0);

		glUseProgram(bodyColor);

		body.Bind();
		body.BufferVertex();
		body.Draw();
		body.Unbind();

		glUseProgram(0);

		glUseProgram(rivetColor);

		leftRivet.Bind();
		leftRivet.BufferVertex();
		leftRivet.Draw();
		leftRivet.Unbind();

		rightRivet.Bind();
		rightRivet.BufferVertex();
		rightRivet.Draw();
		rightRivet.Unbind();

		glUseProgram(0);
	}
}


void Ship::Translate(float x, float y)
{
	body.Translate(x, y);
	thruster.Translate(x, y);
	leftRivet.Translate(x, y);
	rightRivet.Translate(x, y);
	hb.Translate(x, y);
}


void Ship::Rotate(float theta)
{
	float mids[2];
	body.CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	body.Translate(xTranslation, yTranslation);
	body.Swing(theta);
	body.Translate(xTranslation * -1, yTranslation * -1);

	thruster.Translate(xTranslation, yTranslation);
	thruster.Swing(theta);
	thruster.Translate(xTranslation * -1, yTranslation * -1);

	leftRivet.Translate(xTranslation, yTranslation);
	leftRivet.Swing(theta);
	leftRivet.Translate(xTranslation * -1, yTranslation * -1);

	rightRivet.Translate(xTranslation, yTranslation);
	rightRivet.Swing(theta);
	rightRivet.Translate(xTranslation * -1, yTranslation * -1);

	hb.Translate(xTranslation, yTranslation);
	hb.Swing(theta);
	hb.Translate(xTranslation * -1, yTranslation * -1);

}

void Ship::FreeRotate(float theta)
{
	float mids[2];
	body.CalcMidPoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	body.Translate(xTranslation, yTranslation);
	body.FreeSwing(theta);
	body.Translate(xTranslation * -1, yTranslation * -1);

	thruster.Translate(xTranslation, yTranslation);
	thruster.Swing(theta);
	thruster.Translate(xTranslation * -1, yTranslation * -1);

	leftRivet.Translate(xTranslation, yTranslation);
	leftRivet.FreeSwing(theta);
	leftRivet.Translate(xTranslation * -1, yTranslation * -1);

	rightRivet.Translate(xTranslation, yTranslation);
	rightRivet.FreeSwing(theta);
	rightRivet.Translate(xTranslation * -1, yTranslation * -1);

	hb.Translate(xTranslation, yTranslation);
	hb.FreeSwing(theta);
	hb.Translate(xTranslation * -1, yTranslation * -1);
}

void Ship::Swing(float theta)
{
	body.Swing(theta);
	thruster.Swing(theta);
	leftRivet.Swing(theta);
	rightRivet.Swing(theta);
	hb.Swing(theta);
}

void Ship::FreeSwing(float theta)
{
	body.FreeSwing(theta);
	thruster.Swing(theta);
	leftRivet.FreeSwing(theta);
	rightRivet.FreeSwing(theta);
	hb.FreeSwing(theta);
}

float Ship::getCurrentRotation()
{
	float x = 0.0f;

	x += body.getCurrentRotation();
	x += leftRivet.getCurrentRotation();
	x += rightRivet.getCurrentRotation();
	x += hb.getCurrentRotation();

	x = x / 4;

	return x;
}

void Ship::UserMove(GLFWwindow * window)
{


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->Translate(cos(getCurrentRotation()) * movementSpeed * SQ_ASPECT_RATIO, sin(getCurrentRotation()) * movementSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->Rotate(turnSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->Rotate(-1 * turnSpeed);
	}

}


void Ship::Bounce(float bounce)
{
	Boundlimit lim = Unbound;

	if (gameBound.isInBounds(hb) != Unbound)
	{
		lim = gameBound.isInBounds(hb);

		switch (lim)
		{
		case Lower:
			this->Translate(0, bounce);
			break;
		case Right:
			this->Translate(-1 * bounce, 0);
			break;
		case Upper:
			this->Translate(0, bounce * -1);
			break;
		case Left:
			this->Translate(bounce, 0);
			break;
		}
	}

}

bool Ship::isFired(GLFWwindow * win)
{
	if (glfwGetKey(win, 32) == GLFW_PRESS)
	{
		return true;
	}

	return false;
}

void Ship::CalcApproxMidPoint(float m[2])
{
	body.CalcMidPoint(m);
}