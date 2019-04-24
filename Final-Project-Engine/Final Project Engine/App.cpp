#include "Init.h"

int main(void)
{
	int choice = 0;

	do
	{
		system("CLS");
		choice = 0;
		cout << "Welcome to the game! Please select an option\n (1) Play\n (2) Exit\n ";
		while (choice != 1 && choice != 2)
			cin >> choice;
		system("cls");

		if (choice == 1)
		{


			if (!RELEASE_MODE)
			{
				TestClass tests;

				tests.Scoreboard();

				return 0;
			}



			/* Initialize the window */

			if (!glfwInit())
				return -1;



			gameWindow window;

			window.Create(1000, "Game");

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
			s3.setRgb(0.289, 0.51, 0.632);
			s3.Use();
			s3.UpdateUniform();
			s3.unBind();



			bool map[4][4] =
			{
				{false ,false ,false ,true},
				{false, false, false, true},
				{false, false, true, true},
				{false, true, true, true},
			};



			HitArray16 hitarr(0.38, map);

			Triangle t1(0.3, 0.4, 0.5);
			t1.Translate(0.07, -0.55);

			/* Pairs the array and the shape at their origin so the operations can mirror each other about a point*/
			hitarr.Attach(t1);

			hitarr.Translate(0.3, 0.1);
			t1.Translate(0.3, 0.1);
			/* -- */



			long int i = 0;
			long int hit = 0;
			bool life = true;


			Ship ship(0.12, 0.032, s2.ID(), s3.ID());

			Bullet b1;

			while (!glfwWindowShouldClose(window.get()) && life == true)
			{

				if (hit > 100)
				{
					glfwTerminate();
					life = false;
					continue;
				}

				i++;

				/* Render here */
				window.Clear();







				ship.Draw();
				ship.UserMove(window.get());
				ship.Bounce(ship.getSpeed() * 1.5);

				if (ship.isFired(window.get()))
				{
					float ms[2];

					ship.CalcApproxMidPoint(ms);

					b1.Init(ms[0], ms[1], 0.015, 0.1, ship.getCurrentRotation());
					cout << "fire" << endl;
				}

				s2.Use();

				if (b1.getIsInit())
				{
					b1.Draw();
					b1.Fly();
				}

				s2.unBind();












				/* Swap front and back buffers */
				glfwSwapBuffers(window.get());

				/* Poll for and process events */
				glfwPollEvents();
			}



		}


		glfwTerminate();

	} while (choice != 2);


	return 0;
}