#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE    32

char increment(int i);
void pause();
Uint32 SDL_GetTicks( void );

int main(int argc, char* argv[])
{	
	SDL_Event event;
	SDL_Surface *ecran = NULL, *perso = NULL, *touche = NULL, *mur[6] = {NULL}, *grass = NULL,
	 *texte = NULL, *timeText = NULL, *texteMur[6] = {NULL}, *nbrPoint = NULL;
	SDL_Rect position, positionPerso, rcGrass, rcMur[6], rcTouche, rcText, rcTimeText, rcTextMur[6], rcNbrPoint;
	int continuer = 1, tempsPrecedent = 90, tempsActuel = 100, tempsInterval = 300, nbreMystere = 0;
	char pointU[20];
	int point=0;

	TTF_Font *police = NULL;
	srand(time(NULL));


	//position de la fenetre rectangle
	positionPerso.x = 30 ;
	positionPerso.y = 30 ;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	// Initialisation du SONG
	int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
	{
		printf("%s", Mix_GetError());
	}
	  
	//creation des fenetres
	ecran = SDL_SetVideoMode(SCREEN_WIDTH , SCREEN_HEIGHT , 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

	Mix_VolumeMusic(MIX_MAX_VOLUME / 4); 
	Mix_Music *musique, *background; 
	musique = Mix_LoadMUS("sound/GUNFIRE.wav"); 
	background = Mix_LoadMUS("sound/backgrd.wav"); 
	Mix_PlayMusic(background, -1);

	// Textes
	police = TTF_OpenFont("font/FreeSansBold.ttf",25);
	SDL_Color couleurNoire = {0,0,0};
	TTF_SetFontStyle(police, TTF_STYLE_ITALIC);
	
	char timeT[5], timeTextMs[11] = "Time(ms):";
	int timeP = SDL_GetTicks();
	sprintf(timeT,"%i",timeP);
	timeText = TTF_RenderText_Blended(police, timeTextMs, couleurNoire);
	texte = TTF_RenderText_Blended(police, timeT, couleurNoire);

	int i;
	char nbrMur[20];
	for ( i = 0; i < 6; ++i)
	{	
		sprintf(nbrMur," %d",i);
		texteMur[i] = TTF_RenderText_Blended(police,nbrMur, couleurNoire);
	}
	
	

	rcText.x=ecran->w - (texte->w + 30);
	rcText.y=ecran->h - (texte->h);
	rcTimeText.x=ecran->w - (texte->w + 155);
	rcTimeText.y=ecran->h - (texte->h);
	rcNbrPoint.x=0;
	rcNbrPoint.y=ecran->h - (texte->h);

	//load sprite
	perso = IMG_Load("images/mario_bas.gif");
	
	//Load grass
	grass = IMG_Load("images/grass.bmp");

	//Load mur and text
	for (i = 1; i < 6; ++i)
	{
		mur[i] = IMG_Load("images/mur.jpg");
		
	}
	

	//Load foudre
	touche = IMG_Load("images/viseur.png");
	
	//nom de la fenetre
	SDL_WM_SetCaption("Hide And See", NULL);
	
	//couleur de la fenetre
	Uint32 blue = SDL_MapRGB(ecran->format,5,5,14);
	
	const int max=5, min=1;
	
	srand(time(NULL));

	//actualise la surface de l ecran
	SDL_ShowCursor(SDL_DISABLE); 
	SDL_EnableKeyRepeat(10, 5);
	while(continuer){

		SDL_PollEvent(&event);
		
		// sectionz\czxczxczxcz

	switch(event.type){

		case SDL_KEYDOWN :

			switch(event.key.keysym.sym){

				case SDLK_p : 
					SDL_WaitEvent(&event);
				break;			

			}
		}

		// zdaskdjuasdnasmdjhasjdioasd



		 tempsActuel = SDL_GetTicks();

		 // if ( (tempsActuel - tempsPrecedent )< tempsInterval)
		 // {
		 // 	SDL_Delay(tempsInterval - (tempsActuel - tempsPrecedent ));
		 // }
	//Drawing parts like screen, grass and sprite 
	SDL_FillRect( ecran, NULL, blue);

	int x,y;
		for ( x = 0; x < SCREEN_WIDTH; ++x)
		{
			for (y = 0; y < SCREEN_HEIGHT; ++y)
			{	rcGrass.x = x * SPRITE_SIZE;
				rcGrass.y = y * SPRITE_SIZE;
				SDL_BlitSurface(grass,NULL,ecran,&rcGrass);
			}
		}
		sprintf(timeT,"%d",tempsActuel);
		texte = TTF_RenderText_Blended(police, timeT, couleurNoire);
		sprintf(pointU,"Score: %d",point);
		nbrPoint = TTF_RenderText_Blended(police, pointU, couleurNoire);

		SDL_BlitSurface(perso,NULL,ecran,&positionPerso);
		
		// IA de positionemant aleatoire de mario
		char pointU[20];
		int i;
			for (i = 1; i < 6; i++)
			{
				rcMur[i].x = rcTextMur[i].x = 50 * (i + 4) ;
				rcMur[i].y = rcTextMur[i].y = 40 * (i + 4) ; 

				if (tempsActuel - tempsPrecedent > 900){

					nbreMystere=(rand() % (max - min + 1)) + min;
					if (nbreMystere == 1)
					{
						positionPerso.x = rcMur[1].x;
						positionPerso.y = rcMur[1].y - 15;

					}else if (nbreMystere == 2)
					{
						positionPerso.x = rcMur[2].x;
						positionPerso.y = rcMur[2].y - 15; 
					}else if (nbreMystere == 3)
					{
						positionPerso.x = rcMur[3].x;
						positionPerso.y = rcMur[3].y - 15; 
					}else if (nbreMystere == 4)
					{
						positionPerso.x = rcMur[4].x;
						positionPerso.y = rcMur[4].y - 15; 
					}else if (nbreMystere == 5)
					{
						positionPerso.x = rcMur[5].x;
						positionPerso.y = rcMur[5].y - 15; 
					}
					
					
				tempsPrecedent = tempsActuel;


		 		} 

				SDL_BlitSurface(mur[i], NULL, ecran, &rcMur[i]);
				SDL_BlitSurface (texteMur[i], NULL, ecran, &rcTextMur[i]);

				SDL_BlitSurface (nbrPoint, NULL, ecran, &rcNbrPoint);
				SDL_BlitSurface (timeText, NULL, ecran, &rcTimeText);
				SDL_BlitSurface (texte, NULL, ecran, &rcText);
			}

	switch(event.type){

		case SDL_QUIT:
		continuer = 0;
		break;

//		case SDL_MOUSEMOTION :
//		positionPerso.x = event.motion.x;
//		positionPerso.y = event.motion.y;
//		break;

		case SDL_KEYDOWN :

			switch(event.key.keysym.sym){

				case SDLK_ESCAPE : 
				continuer = 0;
				break;

				case SDLK_UP :
				perso = IMG_Load("images/mario_haut.gif");
				positionPerso.y--;
				break;

				case SDLK_DOWN :
				perso = IMG_Load("images/mario_bas.gif");
				positionPerso.y++;
				break;

				case SDLK_RIGHT :
				perso = IMG_Load("images/mario_droite.gif");
				positionPerso.x++ ;
				break;

				case SDLK_LEFT :
				perso = IMG_Load("images/mario_gauche.gif");
				positionPerso.x--;
				break;

				//choose position
				case SDLK_1 :

					if (positionPerso.x == rcMur[1].x && positionPerso.y == rcMur[1].y -15)
					{	
						rcTouche.x = rcMur[1].x-20;
						rcTouche.y = rcMur[1].y-45;
						SDL_BlitSurface(touche,NULL,ecran,&rcTouche);
						sprintf(pointU,"Score: %d",point++);
						nbrPoint = TTF_RenderText_Blended(police, pointU, couleurNoire);
						SDL_BlitSurface (nbrPoint ,NULL, ecran, &rcNbrPoint);
						Mix_PlayMusic(musique, 1);
						Mix_PlayMusic(background, -1);
					}
					
				break;

				case SDLK_2 :

					if (positionPerso.x ==rcMur[2].x && positionPerso.y == rcMur[2].y - 15 )
					{	
						rcTouche.x = rcMur[2].x-20;
						rcTouche.y = rcMur[2].y-45;

						SDL_BlitSurface(touche,NULL,ecran, &rcTouche);
						sprintf(pointU,"Score: %d",point++);
						nbrPoint = TTF_RenderText_Blended(police, pointU, couleurNoire);
						SDL_BlitSurface (nbrPoint ,NULL, ecran, &rcNbrPoint);
						Mix_PlayMusic(musique, 1);
						Mix_PlayMusic(background, -1);
					}
					
				break;

				case SDLK_3 :

					if (positionPerso.x ==rcMur[3].x && positionPerso.y == rcMur[3].y - 15 )
					{	
						rcTouche.x = rcMur[3].x-20;
						rcTouche.y = rcMur[3].y-45;

						SDL_BlitSurface(touche,NULL,ecran,&rcTouche);
						sprintf(pointU,"Score: %d",point++);
						nbrPoint = TTF_RenderText_Blended(police, pointU, couleurNoire);	
						SDL_BlitSurface (nbrPoint ,NULL, ecran, &rcNbrPoint);
						Mix_PlayMusic(musique, 1);
						Mix_PlayMusic(background, -1);
					}
					
				break;

				case SDLK_4 :

					if (positionPerso.x ==rcMur[4].x && positionPerso.y == rcMur[4].y - 15 )
					{	
						rcTouche.x = rcMur[4].x-20;
						rcTouche.y = rcMur[4].y-45;

						SDL_BlitSurface(touche,NULL,ecran,&rcTouche);
						sprintf(pointU,"Score: %d",point++);
						nbrPoint = TTF_RenderText_Blended(police, pointU, couleurNoire);	
						SDL_BlitSurface (nbrPoint ,NULL, ecran, &rcNbrPoint);
						Mix_PlayMusic(musique, 1);
						Mix_PlayMusic(background, -1);
					}
					
				break;

				case SDLK_5 :

					if (positionPerso.x ==rcMur[5].x && positionPerso.y == rcMur[5].y - 15 )
					{	
						rcTouche.x = rcMur[5].x-20;
						rcTouche.y = rcMur[5].y-45;

						SDL_BlitSurface(touche,NULL,ecran,&rcTouche);
						sprintf(pointU,"Score: %d",point++);
						nbrPoint = TTF_RenderText_Blended(police, pointU, couleurNoire);	
						SDL_BlitSurface (nbrPoint ,NULL, ecran, &rcNbrPoint);
						Mix_PlayMusic(musique, 1);
						Mix_PlayMusic(background, -1);
					}
					
				break;

				sprintf(pointU,"%d",point);
				nbrPoint = TTF_RenderText_Blended(police, pointU, couleurNoire);
				SDL_BlitSurface (nbrPoint ,NULL, ecran, &rcNbrPoint);				

			}
		break;
		}
				
					
	SDL_Flip(ecran);
	}
	for (i = 0; i < 6; ++i)
	{
		SDL_FreeSurface(mur[i]); 
	}
	SDL_FreeSurface(grass);
	SDL_FreeSurface(perso);
	SDL_FreeSurface(texteMur[1]);
	SDL_FreeSurface(timeText);
	SDL_FreeSurface(texte);
	SDL_FreeSurface(nbrPoint);
	Mix_FreeMusic(musique);

	Mix_CloseAudio();
	TTF_CloseFont(police);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}

char increment(int i){
	char incr;
	if (i == 1 )
	{
		incr='1';
	}else if (i == 2)
	{
		incr = '2';
	}else if (i == 3)
	{
		incr = '3';
	}else if (i == 4)
	{
		incr = '4';
	}else if (i == 5)
	{
		incr = '5';
	}else if (i == 6)
	{
		incr = '6';
	}else if (i == 7)
	{
		incr = '7';
	}

	return incr;
}

