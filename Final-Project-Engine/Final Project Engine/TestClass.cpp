#include "ExplodeAnimation.h"


int TestClass::HitBoxTranslations()
{

	Notify();


	/* Initialize the window */

	if (!glfwInit())
		return -1;

	gameWindow window;

	window.Create(2000, "Window");

	if (window.validateWindow() == false)
	{
		glfwTerminate();
		return 0;
	}

	window.makeCoreProfile(3, 3);

	window.makeCurrentContext();

	window.vSync(true);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Error" << std::endl;
		return -1;
	}

	Bounds gameBound(1, true, 0.05);


	Shader s2("basic.shader", fourF, 0);
	s2.Create("u_Color");
	s2.setRgb(0.789, 0.11, 0.932);
	s2.Use();
	s2.UpdateUniform();
	s2.unBind();

	Shader s3("basic.shader", fourF, 0);
	s3.Create("u_Color");
	s3.setRgb(0.459, 0.67, 0.354);
	s3.Use();
	s3.UpdateUniform();
	s3.unBind();





	bool map[4][4] =
	{
		{ false ,false ,false ,true },
		{ false, false, false, true },
		{ false, false, true, true },
		{ false, true, true, true },
	};

	/* Paired at origin*/
	HitArray16 hitarr(0.38, map);
	hitarr.TranslateToOrigin();
	Triangle t1(0.3, 0.4, 0.5);
	t1.Translate(0.07, -0.55);
	t1.TranslateToOrigin();

	hitarr.Translate(0.3, 0.1);
	t1.Translate(0.3, 0.1);
	/* -- */



	Hitbox h1(0.1);
	h1.Translate(-0.2, 0.2);

	Circle c1(0.1, 0, 0);
	Hitbox cbox(0.2);

	long int i = 0;

	float arrM[2];

	while (!glfwWindowShouldClose(window.get()))
	{
		i++;
		/* Render here */
		window.Clear();


		s3.Use();

		hitarr.Swing(0.007);
		hitarr.Rotate(0.0045);
		hitarr.DrawMap();

		s3.unBind();



		s2.Use();

		t1.Swing(0.007);
		t1.Rotate(0.0045);
		t1.Bind();
		t1.BufferVertex();
		t1.Draw();
		t1.Unbind();

		h1.Bind();
		h1.BufferVertex();
		h1.Draw();
		h1.Unbind();

		s2.unBind();











		if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
		{
			h1.Translate(0, 0.01);

		}
		if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
		{
			h1.Translate(0, -0.01);

		}
		if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
		{
			h1.Translate(-0.01 * SQ_ASPECT_RATIO, 0);

		}
		if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
		{
			h1.Translate(0.01 * SQ_ASPECT_RATIO, 0);

		}


		if (hitarr.isOverlap(h1))
		{
			cout << "hit" << i << endl;
		}


		Boundlimit bl;

		if (i % 5 == 0)
		{
			bl = gameBound.isInBounds(cbox);

			if (bl != Unbound)
			{
				switch (bl)
				{
				case Upper:
					cout << "upper";
					break;
				case Lower:
					cout << "lower";
					break;
				case Right:
					cout << "right";
					break;
				case Left:
					cout << "left";
					break;
				}

				cout << " " << i << endl;
			}
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window.get());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}




int TestClass::Scoreboard()
{
	Notify();


	/* Initialize the window */

	if (!glfwInit())
		return -1;

	gameWindow window;

	window.Create(2000, "Window");

	if (window.validateWindow() == false)
	{
		glfwTerminate();
		return 0;
	}

	window.makeCoreProfile(3, 3);

	window.makeCurrentContext();

	window.vSync(true);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Error" << std::endl;
		return -1;
	}

	Bounds gameBound(1, true, 0.05);


	Shader s2("basic.shader", fourF, 0);
	s2.Create("u_Color");
	s2.setRgb(0.789, 0.11, 0.932);
	s2.Use();
	s2.UpdateUniform();
	s2.unBind();

	Shader s3("basic.shader", fourF, 0);
	s3.Create("u_Color");
	s3.setRgb(0.459, 0.67, 0.354);
	s3.Use();
	s3.UpdateUniform();
	s3.unBind();





	bool map[4][4] =
	{
		{ false ,false ,false ,true },
		{ false, false, false, true },
		{ false, false, true, true },
		{ false, true, true, true },
	};

	/* Paired at origin*/
	HitArray16 hitarr(0.38, map);
	hitarr.TranslateToOrigin();
	Triangle t1(0.3, 0.4, 0.5);
	t1.Translate(0.07, -0.55);
	t1.TranslateToOrigin();

	hitarr.Translate(0.3, 0.1);
	t1.Translate(0.3, 0.1);
	/* -- */


	ScoreBoard board(5, 0.3, 0.5, 0.5, 0.25);

	long int i = 0;


	while (!glfwWindowShouldClose(window.get()))
	{
		i++;
		/* Render here */
		window.Clear();

		s3.Use();

		if (i % 10 == 0)
			board.incr();

		board.Draw();

		cout << board.getRealNum() << endl;

		s3.unBind();



		/* Swap front and back buffers */
		glfwSwapBuffers(window.get());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


/*  */



int TestClass::KeepTriangleInbounds()
{


	Notify();

	/* Initialize the window */

	if (!glfwInit())
		return -1;

	gameWindow window;

	window.Create(2000, "Game");

	if (window.validateWindow() == false)
	{
		glfwTerminate();
		return 0;
	}

	window.makeCoreProfile(3, 3);

	window.makeCurrentContext();

	window.vSync(true);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Error" << std::endl;
		return -1;
	}


	Bounds gameBound(1, true, 0.005);


	Shader s2("basic.shader", fourF, 0);
	s2.Create("u_Color");
	s2.setRgb(0.789, 0.11, 0.932);
	s2.Use();
	s2.UpdateUniform();
	s2.unBind();

	Shader s3("basic.shader", fourF, 0);
	s3.Create("u_Color");
	s3.setRgb(0.459, 0.67, 0.354);
	s3.Use();
	s3.UpdateUniform();
	s3.unBind();





	bool map[4][4] =
	{
		{ false ,false ,false ,true },
		{ false, false, false, true },
		{ false, false, true, true },
		{ false, true, true, true },
	};



	HitArray16 hitarr(0.38, map);

	Triangle t1(0.3, 0.4, 0.5);
	t1.Translate(0.07, -0.55);

	/* Pairs the array and the shape at their origin so the operations can mirror each other about a point*/
	hitarr.Attach(t1);


	hitarr.Translate(0.3, 0.1);
	t1.Translate(0.3, 0.1);
	/* -- */



	Hitbox h1(0.3);
	h1.Translate(-0.2, 0.2);

	Circle c1(0.2, 0, 0);
	Hitbox cbox(0.2);


	long int i = 0;

	float arrM[2];

	while (!glfwWindowShouldClose(window.get()))
	{
		i++;
		/* Render here */
		window.Clear();


		s3.Use();

		hitarr.Rotate(0.045);
		//	hitarr.DrawMap();

		s3.unBind();



		s2.Use();

		t1.Rotate(0.045);
		t1.Bind();
		t1.BufferVertex();
		t1.Draw();
		t1.Unbind();

		h1.Bind();
		h1.BufferVertex();
		h1.Draw();
		h1.Unbind();

		s2.unBind();








		Boundlimit lim = Unbound;


		if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
		{
			if (gameBound.isInBounds(hitarr) != Upper)
			{
				hitarr.Translate(0, 0.01);
				t1.Translate(0, 0.01);
			}

			lim = gameBound.isInBounds(hitarr);

			gameBound.Bounce(lim, hitarr, true, &t1);

		}
		if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
		{
			if (gameBound.isInBounds(hitarr) != Lower)
			{
				hitarr.Translate(0, -0.01);
				t1.Translate(0, -0.01);
			}

			lim = gameBound.isInBounds(hitarr);

			gameBound.Bounce(lim, hitarr, true, &t1);

		}
		if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
		{
			if (gameBound.isInBounds(hitarr) != Left)
			{
				hitarr.Translate(-0.01 * SQ_ASPECT_RATIO, 0);
				t1.Translate(-0.01 * SQ_ASPECT_RATIO, 0);
			}

			lim = gameBound.isInBounds(hitarr);

			gameBound.Bounce(lim, hitarr, true, &t1);

		}
		if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
		{
			if (gameBound.isInBounds(hitarr) != Right)
			{
				hitarr.Translate(0.01 * SQ_ASPECT_RATIO, 0);
				t1.Translate(0.01 * SQ_ASPECT_RATIO, 0);
			}

			lim = gameBound.isInBounds(hitarr);

			gameBound.Bounce(lim, hitarr, true, &t1);

		}


		if (hitarr.isOverlap(h1))
		{
			cout << "hit" << i << endl;
		}


		Boundlimit bl;

		if (i % 5 == 0)
		{
			bl = gameBound.isInBounds(hitarr);

			if (bl != Unbound)
			{
				switch (bl)
				{
				case Upper:
					cout << "upper";
					break;
				case Lower:
					cout << "lower";
					break;
				case Right:
					cout << "right";
					break;
				case Left:
					cout << "left";
					break;
				}

				cout << " " << i << endl;
			}
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window.get());

		/* Poll for and process events */
		glfwPollEvents();
	}






	glfwTerminate();
	return 0;
}


/*  */

int TestClass::FreeMovements()
{


	Notify();

	/* Initialize the window */

	if (!glfwInit())
		return -1;

	gameWindow window;

	window.Create(2000, "Game");

	if (window.validateWindow() == false)
	{
		glfwTerminate();
		return 0;
	}

	window.makeCoreProfile(3, 3);

	window.makeCurrentContext();

	window.vSync(true);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Error" << std::endl;
		return -1;
	}


	Bounds gameBound(1, true, 0.005);


	Shader s2("basic.shader", fourF, 0);
	s2.Create("u_Color");
	s2.setRgb(0.789, 0.11, 0.932);
	s2.Use();
	s2.UpdateUniform();
	s2.unBind();

	Shader s3("basic.shader", fourF, 0);
	s3.Create("u_Color");
	s3.setRgb(0.459, 0.67, 0.354);
	s3.Use();
	s3.UpdateUniform();
	s3.unBind();





	bool map[4][4] =
	{
		{ false ,false ,false ,false },
		{ true, true, true, true },
		{ true, true, true, true },
		{ true, true, true, true },
	};



	HitArray16 hitarr(0.2f, map);


	Triangle t1(0.4, 0.4, 0.4);

	/* Pairs the array and the shape at their origin so the operations can mirror each other about a point*/
	hitarr.Attach(t1);


	t1.Rotate(1.57);
	hitarr.Rotate(1.57);

	t1.FreeRotate(-1.59);
	hitarr.FreeRotate(-1.59);



	/* -- */



	Hitbox h1(0.3);
	h1.Translate(-0.2, 0.2);

	Circle c1(0.2, 0, 0);
	Hitbox cbox(0.2);


	long int i = 0;

	float arrM[2];

	while (!glfwWindowShouldClose(window.get()))
	{
		i++;
		/* Render here */
		window.Clear();


		s3.Use();

		hitarr.DrawMap();

		s3.unBind();



		s2.Use();

		t1.Bind();
		t1.BufferVertex();
		t1.Draw();
		t1.Unbind();

		h1.Bind();
		h1.BufferVertex();
		h1.Draw();
		h1.Unbind();

		s2.unBind();








		Boundlimit lim = Unbound;

		float x = 0.02;

		if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
		{
			t1.Translate(cos(t1.getCurrentRotation()) * x * SQ_ASPECT_RATIO, sin(t1.getCurrentRotation()) * x);
			hitarr.Translate(cos(t1.getCurrentRotation()) * x * SQ_ASPECT_RATIO, sin(t1.getCurrentRotation()) * x);
		}
		if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
		{
			hitarr.Rotate(0.045);
			t1.Rotate(0.045);
		}
		if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
		{
			hitarr.Rotate(-1 * 0.045);
			t1.Rotate(-1 * 0.045);
		}


		if (hitarr.isOverlap(h1))
		{
			cout << "hit" << i << endl;
		}


		Boundlimit bl;

		if (i % 5 == 0)
		{
			bl = gameBound.isInBounds(hitarr);

			if (bl != Unbound)
			{
				switch (bl)
				{
				case Upper:
					cout << "upper";
					break;
				case Lower:
					cout << "lower";
					break;
				case Right:
					cout << "right";
					break;
				case Left:
					cout << "left";
					break;
				}

				cout << " " << i << endl;
			}
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window.get());

		/* Poll for and process events */
		glfwPollEvents();
	}






	glfwTerminate();
	return 0;

}


int TestClass::HitAnimation()
{


	Notify();

	/* Initialize the window */

	if (!glfwInit())
		return -1;

	gameWindow window;

	window.Create(2000, "Game");

	if (window.validateWindow() == false)
	{
		glfwTerminate();
		return 0;
	}

	window.makeCoreProfile(3, 3);

	window.makeCurrentContext();

	window.vSync(true);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Error" << std::endl;
		return -1;
	}


	Bounds gameBound(1, true, 0.005);


	Shader s2("basic.shader", fourF, 0);
	s2.Create("u_Color");
	s2.setRgb(0.789, 0.11, 0.932);
	s2.Use();
	s2.UpdateUniform();
	s2.unBind();

	Shader s3("basic.shader", fourF, 0);
	s3.Create("u_Color");
	s3.setRgb(0.459, 0.67, 0.354);
	s3.Use();
	s3.UpdateUniform();
	s3.unBind();





	bool map[4][4] =
	{
		{ false ,false ,false ,false },
		{ true, true, true, true },
		{ true, true, true, true },
		{ true, true, true, true },
	};



	HitArray16 hitarr(0.2f, map);


	Triangle t1(0.4, 0.4, 0.4);

	/* Pairs the array and the shape at their origin so the operations can mirror each other about a point*/
	hitarr.Attach(t1);


	t1.Rotate(1.57);
	hitarr.Rotate(1.57);

	t1.FreeRotate(-1.59);
	hitarr.FreeRotate(-1.59);



	/* -- */



	Hitbox h1(0.3);
	h1.Translate(-0.2, 0.2);

	Circle c1(0.2, 0, 0);
	Hitbox cbox(0.2);

	EnemyExplode e1(0.0, 0.0, 0.1);


	long int i = 0;

	float arrM[2];

	while (!glfwWindowShouldClose(window.get()))
	{
		i++;
		/* Render here */
		window.Clear();


		s3.Use();


		s3.unBind();


		e1.Draw();
		e1.iterate();





		Boundlimit lim = Unbound;

		float x = 0.02;

		if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
		{
			t1.Translate(cos(t1.getCurrentRotation()) * x * SQ_ASPECT_RATIO, sin(t1.getCurrentRotation()) * x);
			hitarr.Translate(cos(t1.getCurrentRotation()) * x * SQ_ASPECT_RATIO, sin(t1.getCurrentRotation()) * x);
		}
		if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
		{
			hitarr.Rotate(0.045);
			t1.Rotate(0.045);
		}
		if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
		{
			hitarr.Rotate(-1 * 0.045);
			t1.Rotate(-1 * 0.045);
		}


		if (hitarr.isOverlap(h1))
		{
			cout << "hit" << i << endl;
		}


		Boundlimit bl;

		if (i % 5 == 0)
		{
			bl = gameBound.isInBounds(hitarr);

			if (bl != Unbound)
			{
				switch (bl)
				{
				case Upper:
					cout << "upper";
					break;
				case Lower:
					cout << "lower";
					break;
				case Right:
					cout << "right";
					break;
				case Left:
					cout << "left";
					break;
				}

				cout << " " << i << endl;
			}
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window.get());

		/* Poll for and process events */
		glfwPollEvents();
	}






	glfwTerminate();
	return 0;

}