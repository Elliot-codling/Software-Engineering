#include "Game.h"
#include <windows.h>
#include <iostream>
#include "../Core/Utils.h"
#include "../Core/Renderer/ASCIIRenderer.h"

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 96;

#define VK_LEFT		0x25
#define VK_RIGHT	0x27
#define VK_SPACE	0x20       

char* GameTitleSprite = "                                                                                                                                                                            dddddddd                                                                        AAA                 SSSSSSSSSSSSSSS         CCCCCCCCCCCCCIIIIIIIIIIIIIIIIIIII     IIIIIIIIII                                                                 d::::::d                                                                       A:::A              SS:::::::::::::::S     CCC::::::::::::CI::::::::II::::::::I     I::::::::I                                                                 d::::::d                                                                      A:::::A            S:::::SSSSSS::::::S   CC:::::::::::::::CI::::::::II::::::::I     I::::::::I                                                                 d::::::d                                                                     A:::::::A           S:::::S     SSSSSSS  C:::::CCCCCCCC::::CII::::::IIII::::::II     II::::::II                                                                 d:::::d                                                                     A:::::::::A          S:::::S             C:::::C       CCCCCC  I::::I    I::::I         I::::Innnn  nnnnnnnn vvvvvvv           vvvvvvvaaaaaaaaaaaaa      ddddddddd:::::d     eeeeeeeeeeee    rrrrr   rrrrrrrrr       ssssssssss             A:::::A:::::A         S:::::S            C:::::C                I::::I    I::::I         I::::In:::nn::::::::nnv:::::v         v:::::v a::::::::::::a   dd::::::::::::::d   ee::::::::::::ee  r::::rrr:::::::::r    ss::::::::::s           A:::::A A:::::A         S::::SSSS         C:::::C                I::::I    I::::I         I::::In::::::::::::::nnv:::::v       v:::::v  aaaaaaaaa:::::a d::::::::::::::::d  e::::::eeeee:::::eer:::::::::::::::::r ss:::::::::::::s         A:::::A   A:::::A         SS::::::SSSSS    C:::::C                I::::I    I::::I         I::::Inn:::::::::::::::nv:::::v     v:::::v            a::::ad:::::::ddddd:::::d e::::::e     e:::::err::::::rrrrr::::::rs::::::ssss:::::s       A:::::A     A:::::A          SSS::::::::SS  C:::::C                I::::I    I::::I         I::::I  n:::::nnnn:::::n v:::::v   v:::::v      aaaaaaa:::::ad::::::d    d:::::d e:::::::eeeee::::::e r:::::r     r:::::r s:::::s  ssssss       A:::::AAAAAAAAA:::::A            SSSSSS::::S C:::::C                I::::I    I::::I         I::::I  n::::n    n::::n  v:::::v v:::::v     aa::::::::::::ad:::::d     d:::::d e:::::::::::::::::e  r:::::r     rrrrrrr   s::::::s           A:::::::::::::::::::::A                S:::::SC:::::C                I::::I    I::::I         I::::I  n::::n    n::::n   v:::::v:::::v     a::::aaaa::::::ad:::::d     d:::::d e::::::eeeeeeeeeee   r:::::r                  s::::::s       A:::::AAAAAAAAAAAAA:::::A               S:::::S C:::::C       CCCCCC  I::::I    I::::I         I::::I  n::::n    n::::n    v:::::::::v     a::::a    a:::::ad:::::d     d:::::d e:::::::e            r:::::r            ssssss   s:::::s    A:::::A             A:::::A  SSSSSSS     S:::::S  C:::::CCCCCCCC::::CII::::::IIII::::::II     II::::::IIn::::n    n::::n     v:::::::v      a::::a    a:::::ad::::::ddddd::::::dde::::::::e           r:::::r            s:::::ssss::::::s  A:::::A               A:::::A S::::::SSSSSS:::::S   CC:::::::::::::::CI::::::::II::::::::I     I::::::::In::::n    n::::n      v:::::v       a:::::aaaa::::::a d:::::::::::::::::d e::::::::eeeeeeee   r:::::r            s::::::::::::::s  A:::::A                 A:::::AS:::::::::::::::SS      CCC::::::::::::CI::::::::II::::::::I     I::::::::In::::n    n::::n       v:::v         a::::::::::aa:::a d:::::::::ddd::::d  ee:::::::::::::e   r:::::r             s:::::::::::ss  AAAAAAA                   AAAAAAASSSSSSSSSSSSSSS           CCCCCCCCCCCCCIIIIIIIIIIIIIIIIIIII     IIIIIIIIIInnnnnn    nnnnnn        vvv           aaaaaaaaaa  aaaa  ddddddddd   ddddd    eeeeeeeeeeeeee   rrrrrrr              sssssssssss    ";
char* GameOverSprite = "        GGGGGGGGGGGGG               AAA               MMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE          OOOOOOOOO     VVVVVVVV           VVVVVVVVEEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR        GGG::::::::::::G              A:::A              M:::::::M             M:::::::ME::::::::::::::::::::E        OO:::::::::OO   V::::::V           V::::::VE::::::::::::::::::::ER::::::::::::::::R     GG:::::::::::::::G             A:::::A             M::::::::M           M::::::::ME::::::::::::::::::::E      OO:::::::::::::OO V::::::V           V::::::VE::::::::::::::::::::ER::::::RRRRRR:::::R   G:::::GGGGGGGG::::G            A:::::::A            M:::::::::M         M:::::::::MEE::::::EEEEEEEEE::::E     O:::::::OOO:::::::OV::::::V           V::::::VEE::::::EEEEEEEEE::::ERR:::::R     R:::::R G:::::G       GGGGGG           A:::::::::A           M::::::::::M       M::::::::::M  E:::::E       EEEEEE     O::::::O   O::::::O V:::::V           V:::::V   E:::::E       EEEEEE  R::::R     R:::::RG:::::G                        A:::::A:::::A          M:::::::::::M     M:::::::::::M  E:::::E                  O:::::O     O:::::O  V:::::V         V:::::V    E:::::E               R::::R     R:::::RG:::::G                       A:::::A A:::::A         M:::::::M::::M   M::::M:::::::M  E::::::EEEEEEEEEE        O:::::O     O:::::O   V:::::V       V:::::V     E::::::EEEEEEEEEE     R::::RRRRRR:::::R G:::::G    GGGGGGGGGG        A:::::A   A:::::A        M::::::M M::::M M::::M M::::::M  E:::::::::::::::E        O:::::O     O:::::O    V:::::V     V:::::V      E:::::::::::::::E     R:::::::::::::RR  G:::::G    G::::::::G       A:::::A     A:::::A       M::::::M  M::::M::::M  M::::::M  E:::::::::::::::E        O:::::O     O:::::O     V:::::V   V:::::V       E:::::::::::::::E     R::::RRRRRR:::::R G:::::G    GGGGG::::G      A:::::AAAAAAAAA:::::A      M::::::M   M:::::::M   M::::::M  E::::::EEEEEEEEEE        O:::::O     O:::::O      V:::::V V:::::V        E::::::EEEEEEEEEE     R::::R     R:::::RG:::::G        G::::G     A:::::::::::::::::::::A     M::::::M    M:::::M    M::::::M  E:::::E                  O:::::O     O:::::O       V:::::V:::::V         E:::::E               R::::R     R:::::R G:::::G       G::::G    A:::::AAAAAAAAAAAAA:::::A    M::::::M     MMMMM     M::::::M  E:::::E       EEEEEE     O::::::O   O::::::O        V:::::::::V          E:::::E       EEEEEE  R::::R     R:::::R  G:::::GGGGGGGG::::G   A:::::A             A:::::A   M::::::M               M::::::MEE::::::EEEEEEEE:::::E     O:::::::OOO:::::::O         V:::::::V         EE::::::EEEEEEEE:::::ERR:::::R     R:::::R   GG:::::::::::::::G  A:::::A               A:::::A  M::::::M               M::::::ME::::::::::::::::::::E      OO:::::::::::::OO           V:::::V          E::::::::::::::::::::ER::::::R     R:::::R     GGG::::::GGG:::G A:::::A                 A:::::A M::::::M               M::::::ME::::::::::::::::::::E        OO:::::::::OO              V:::V           E::::::::::::::::::::ER::::::R     R:::::R        GGGGGG   GGGGAAAAAAA                   AAAAAAAMMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE          OOOOOOOOO                 VVV            EEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR";
char* YouWinSprite = "YYYYYYY       YYYYYYY     OOOOOOOOO     UUUUUUUU     UUUUUUUU     WWWWWWWW                           WWWWWWWWIIIIIIIIIINNNNNNNN        NNNNNNNNY:::::Y       Y:::::Y   OO:::::::::OO   U::::::U     U::::::U     W::::::W                           W::::::WI::::::::IN:::::::N       N::::::NY:::::Y       Y:::::Y OO:::::::::::::OO U::::::U     U::::::U     W::::::W                           W::::::WI::::::::IN::::::::N      N::::::NY::::::Y     Y::::::YO:::::::OOO:::::::OUU:::::U     U:::::UU     W::::::W                           W::::::WII::::::IIN:::::::::N     N::::::NYYY:::::Y   Y:::::YYYO::::::O   O::::::O U:::::U     U:::::U       W:::::W           WWWWW           W:::::W   I::::I  N::::::::::N    N::::::N   Y:::::Y Y:::::Y   O:::::O     O:::::O U:::::D     D:::::U        W:::::W         W:::::W         W:::::W    I::::I  N:::::::::::N   N::::::N    Y:::::Y:::::Y    O:::::O     O:::::O U:::::D     D:::::U         W:::::W       W:::::::W       W:::::W     I::::I  N:::::::N::::N  N::::::N     Y:::::::::Y     O:::::O     O:::::O U:::::D     D:::::U          W:::::W     W:::::::::W     W:::::W      I::::I  N::::::N N::::N N::::::N      Y:::::::Y      O:::::O     O:::::O U:::::D     D:::::U           W:::::W   W:::::W:::::W   W:::::W       I::::I  N::::::N  N::::N:::::::N       Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U            W:::::W W:::::W W:::::W W:::::W        I::::I  N::::::N   N:::::::::::N       Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U             W:::::W:::::W   W:::::W:::::W         I::::I  N::::::N    N::::::::::N       Y:::::Y       O::::::O   O::::::O U::::::U   U::::::U              W:::::::::W     W:::::::::W          I::::I  N::::::N     N:::::::::N       Y:::::Y       O:::::::OOO:::::::O U:::::::UUU:::::::U               W:::::::W       W:::::::W         II::::::IIN::::::N      N::::::::N    YYYY:::::YYYY     OO:::::::::::::OO   UU:::::::::::::UU                 W:::::W         W:::::W          I::::::::IN::::::N       N:::::::N    Y:::::::::::Y       OO:::::::::OO       UU:::::::::UU                    W:::W           W:::W           I::::::::IN::::::N        N::::::N    YYYYYYYYYYYYY         OOOOOOOOO           UUUUUUUUU                       WWW             WWW            IIIIIIIIIINNNNNNNN         NNNNNNN";

Game::Game()
:m_pRenderer(NULL)
, m_GameState(E_GAME_STATE_MAIN_MENU)
, m_bInitialised(false)
, m_bExitApp(false)
, m_Score(0)
, m_MainMenuCounter(0)
, m_EndScreenCounter(0)
{
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pRenderer);
}

void Game::Initialise()
{
	InitialiseRenderer();

	InitialiseMainMenu();

	InitialiseGame();

	InitialiseEndScreens();

	m_bInitialised = true;
}

void Game::InitialiseRenderer()
{
	m_pRenderer = new ASCIIRenderer();

	m_pRenderer->Initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::InitialiseMainMenu()
{
	//Main Menu
	Vector2 titleSize(237, 17);
	m_GameTitle.Initialise(GameTitleSprite, FOREGROUND_WHITE, titleSize);

	Vector2 startPosition(10, 38);
	m_GameTitle.SetPosition(startPosition);
}

void Game::InitialiseGame()
{
	//Game
	m_PlayerShip.Initialise(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 8), VK_LEFT, VK_RIGHT);

	m_EnemyArmy.Initialise(this);

	m_Missile.Initialise(Vector2(m_PlayerShip.GetPosition().x + (m_PlayerShip.GetSize().x * 0.5f), m_PlayerShip.GetPosition().y - 2), Vector2(0, -MISSILE_SPEED));
	m_Missile.SetActive(false);


	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Initialise(Vector2(7 + (i * 10), 7));
	}
}

void Game::InitialiseEndScreens()
{
	//End Game Screen
	Vector2 gameOverTitleSize(200, 16);
	m_GameOverTitle.Initialise(GameOverSprite, FOREGROUND_WHITE, gameOverTitleSize);

	Vector2 gameOverPosition(25, 37);
	m_GameOverTitle.SetPosition(gameOverPosition);


	Vector2 youWinTitleSize(143, 16);
	m_YouWinTitle.Initialise(YouWinSprite, FOREGROUND_WHITE, youWinTitleSize);

	Vector2 youWinPosition(53, 37);
	m_YouWinTitle.SetPosition(youWinPosition);
}

void Game::Run()
{
	while (!m_bExitApp)
	{
		Update();

		Render();

		Sleep(30);
	}
}

void Game::Update()
{
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		m_bExitApp = true;
		return;
	}

	switch (m_GameState)
	{
		case E_GAME_STATE_MAIN_MENU:
		{
			UpdateMainMenu();
		}
		break;

		case E_GAME_STATE_IN_GAME:
		{
			UpdateGame();				
		}
		break;

		case E_GAME_STATE_WIN_GAME: //fall through
		case E_GAME_STATE_LOSE_GAME:
		{
			UpdateEndGameScreens();
		}
		break;

		default:
		{
		}
	}
}

void Game::UpdateMainMenu()
{
	m_MainMenuCounter++;

	if (m_MainMenuCounter > 60)
	{
		m_MainMenuCounter = 0;
		m_GameState = E_GAME_STATE_IN_GAME;
	}
}

void Game::UpdateGame()
{
	
}

void Game::FireMissile()
{
	m_Missile.SetPosition(m_PlayerShip.GetPosition().x + (m_PlayerShip.GetSize().x * 0.5f), m_PlayerShip.GetPosition().y - 2);
	m_Missile.SetActive();
}

void Game::UpdatePlayerMissiles()
{
	m_Missile.Update();

	if (m_Missile.GetPosition().y < 0 || m_Missile.GetPosition().y > SCREEN_HEIGHT)
	{
		m_Missile.Explode();
	}

	if (m_Missile.Active() && m_EnemyArmy.Collides(m_Missile))
	{
		m_Score += m_EnemyArmy.GetScore();
		m_Missile.Explode();
	}

}

void Game::UpdateEnemyMissiles()
{
	for (int i = 0; i < m_EnemyMissiles.size(); i++)
	{
		m_EnemyMissiles[i]->Update();
	}

	for (int i = 0; i < m_EnemyMissiles.size(); i++)
	{
		if (m_EnemyMissiles[i]->Active() && m_EnemyMissiles[i]->Collides(m_PlayerShip))
		{
			//hit the player
			m_EnemyMissiles[i]->Explode();
			m_GameState = E_GAME_STATE_LOSE_GAME;
		}
		if (m_EnemyMissiles[i]->Active() && m_EnemyMissiles[i]->GetPosition().y > SCREEN_HEIGHT)
		{
			m_EnemyMissiles[i]->Explode();
		}
	}
}

void Game::CheckWinConditions()
{
	if (m_EnemyArmy.GetNumActiveEnemies() <= 0)
	{
		//player wins
		m_GameState = E_GAME_STATE_WIN_GAME;
	}
	else if (m_EnemyArmy.HasLanded())
	{
		//player loses
		m_GameState = E_GAME_STATE_LOSE_GAME;
	}
}

void Game::UpdateEndGameScreens()
{
	m_EndScreenCounter++;

	if (m_EndScreenCounter > 90)
	{
		m_EndScreenCounter = 0;
		m_bExitApp = true;
	}
}

void Game::Render()
{
	m_pRenderer->ClearScreen();	

	switch (m_GameState)
	{
		case E_GAME_STATE_MAIN_MENU:
		{
			RenderMainMenu();
		}
		break;

		case E_GAME_STATE_IN_GAME:
		{
			RenderGame();
		}
		break;

		case E_GAME_STATE_WIN_GAME:
		{
			RenderWinScreen();
		}
		break;

		case E_GAME_STATE_LOSE_GAME:
		{
			RenderLoseScreen();
		}
		break;

		default:
		{
		}
	}

	//call this last
	m_pRenderer->Render();
}

void Game::RenderMainMenu()
{
	m_GameTitle.Render(m_pRenderer);
}

void Game::RenderGame()
{
	m_PlayerShip.Render(m_pRenderer);

	RenderScore();
}

void Game::RenderEnemyMissiles()
{
	for (int i = 0; i < m_EnemyMissiles.size(); i++)
	{
		m_EnemyMissiles[i]->Render(m_pRenderer);
	}
}

void Game::RenderScore()
{
	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Render(m_pRenderer);
	}
}

void Game::RenderWinScreen()
{
	m_YouWinTitle.Render(m_pRenderer);
}

void Game::RenderLoseScreen()
{
	m_GameOverTitle.Render(m_pRenderer);
}

void Game::AddEnemyMissile(Missile* pMissile)
{
	m_EnemyMissiles.push_back(pMissile);
}

void Game::UpdateScoreDisplay()
{
	for (int i = 0; i < 4; i++)
	{
		m_ScoreDigit[i].Update(0.0f);
	}

	int ScoreValues[4];

	ScoreValues[3] = m_Score > 9999 ? 9 : m_Score % 10;
	ScoreValues[2] = m_Score > 9999 ? 9 : m_Score / 10 % 10;
	ScoreValues[1] = m_Score > 9999 ? 9 : m_Score / 100 % 10;
	ScoreValues[0] = m_Score > 9999 ? 9 : m_Score / 1000 % 10;

	m_ScoreDigit[0].SetDigitValue(ScoreValues[0]);
	m_ScoreDigit[1].SetDigitValue(ScoreValues[1]);
	m_ScoreDigit[2].SetDigitValue(ScoreValues[2]);
	m_ScoreDigit[3].SetDigitValue(ScoreValues[3]);
}
