#include "ExplodeAnimation.h"

int main(void)
{



	/* Uncomment Test Functions */
	if (RELEASE_MODE == false)
	{
		TestClass tests;

	//	tests.HitAnimation();
	//	tests.FreeMovements();
	//	tests.HitBoxTranslations();
	//	tests.KeepTriangleInbounds();
	//	tests.Scoreboard();
	}




	int choice = 0;

	int score = 0;

	srand((unsigned int)time(NULL));

	do
	{
		if (score != 0)
		{
			system("cls");

			cout << endl << endl << "You Scored: " << score  << "!" << endl << endl << endl;

			score = 0;

			system("pause");
			system("cls");
		}


		choice = 0;
		cout << endl << "1) Play Game" << endl << endl<< "2) Exit" << endl;;

		cout << endl;

		cout << "Hot To Play:" << endl << endl;

		cout << "- Press W to move Foward" << endl;
		cout << "- Press D to rotate clockwise" << endl;
		cout << "- Press A to rotate counter-clockwise" << endl;
		cout << "- Press SPACE to fire at enemies" << endl << endl;

		cout << "Kill as many as you can, if you are hit by an enemy the game is over!" << endl << endl;


		while (choice != 1 && choice != 2)
			cin >> choice;
		system("cls");

		if (choice == 1)
		{



			/* Initialize the window */

			if (!glfwInit())
				return -1;



			gameWindow window;

			window.Create(2000, "Spaceship");

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



			/* Shader Compilation */

			Shader s2("basic.shader", fourF, 0);
			s2.Create("u_Color");
			s2.setRgb(0.2, 0.31, 0.542);
			s2.Use();
			s2.UpdateUniform();
			s2.unBind();

			Shader s3("basic.shader", fourF, 0);
			s3.Create("u_Color");
			s3.setRgb(1.0, 0.51, 0.0);
			s3.Use();
			s3.UpdateUniform();
			s3.unBind();

			Shader s4("basic.shader", fourF, 0);
			s4.Create("u_Color");
			s4.setRgb(1.0, 0.0, 0.0);
			s4.Use();
			s4.UpdateUniform();
			s4.unBind();




			long int i = 0;
			long int timer = 0;

			long int hit = 0;
			bool life = true;




			Bounds gameBound(1, true, 0.005);

			Ship ship(PI / 24.0f, 0.025f, s2.ID(), s3.ID());
			ship.Translate(0.7, -0.7);

			Mag mag(0.08, 0.02, s3.ID());
			FireTimer ftimer(10);

			ScoreBoard board(6, 0.15, 0.82, 0.87, 0.12);

			Swarm swarm(0.012, 0.0095, 0.1, 0.1, s4.ID());

			EnemyExplode earr[10];
			for (int i = 0; i < 10; i++)
			{
				earr[i].Init(2.0f, 2.0f, 0.08);
			}
			int animationIndex = -1;

			
			


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





				// HIT ANIMATIONS LAY IN THE BACKGROUND SO THEY ARE DRAWN FIRST
				for (int i = 0; i < 10; i++)
				{
					earr[i].Draw();
					earr[i].iterate();
				}

				/* Draw The Board Near The Back Of The Scene*/
				board.Draw();


				/*Spawn Enemies In Random Corners*/
				float xS = 0.9;
				float yS = 0.9;
				if (i % 60 == 0)
				{
					if(rand() % 3 == 0)
					swarm.Spawn(-1 * xS, -1 * yS);
					else if(rand() % 3 == 1)
					swarm.Spawn(-1 * xS, yS);
					else
					swarm.Spawn(xS, yS);

				}


				/* Draw The Ship : Poll For User Input : Bounce She Ship Off Any Barriers*/
				ship.Draw();
				ship.UserMove(window.get());
				ship.Bounce(ship.getSpeed() * 1.5);


					/* Fire From The Magazine If The User Fires*/
					if (ship.isFired(window.get()) && ftimer.IsGoodFire(i))
					{
						float ms[2];
						ship.CalcApproxMidPoint(ms);
						mag.Shoot(ms[0], ms[1], ship.getCurrentRotation());
					}


				/*Update All Bullets In The Air*/
				mag.Ping();

				/*Update All Enemies In The Air*/
				swarm.Ping();



				/*Check For Contact and Destruct Enemies And Bullets Using Member Functions*/
				for (int i = 0; i < 16; i++)
				{
					Hitbox * temp;

					temp = swarm.getHitBox(i);

					if (temp != nullptr)
					{
						if (mag.isContact(*temp))
						{
							float eM[2];

							swarm.getMids(i, eM);

							swarm.Kill(i);

							animationIndex += 1;

							if (animationIndex == 9)
								animationIndex = 0;

							earr[animationIndex].Init(eM[0], eM[1], 0.08);

							board.incr();

						}
					}

				}

				/* Check if the ship has been hit by an enemy in which case the game is over*/
				if (swarm.checkForDamage(*(ship.getBox())) != -1)
				{
					life = false;
					score = board.getRealNum();
				}
				



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