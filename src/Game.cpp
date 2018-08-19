#include "Game.hpp"

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <SDL.h>

int play_fmv(int movie, int resize) {
	int movie_ptr = 0;
	int video_ptr = 0;
	int sound_ptr = 0;
	int something2 = 0;
	int something3 = 0;
	int frames = 0;
	int current_frame = 0;
	int movieX = 0;
	int movieY = 0;

	TOMB_CALLPROC(0x0040837F);
	
	char** fmvs = TOMB_ADDRESS(0x00453AC0, char*);
	std::cout << "Playing " << fmvs[movie] << std::endl;
	int dir = TOMB_PROC_PTR<int, int>(0x0041BFC0)((int)fmvs[movie]);

	if (TOMB_PROC_PTR<int, int*, int, int, int, int>(0x004504FA)(&movie_ptr, 0, 0, dir, 0x100000)) {
		return 0;
	}
	
	if (resize) {
		movieY = TOMB_PROC_PTR<int, int>(0x004504F4)(movie_ptr);
		something2 = 13;
		something3 = (480 - 2 * movieY) >> 1;
	}
	
	movieX = TOMB_PROC_PTR<int, int>(0x004504EE)(movie_ptr);
	movieY = TOMB_PROC_PTR<int, int>(0x004504F4)(movie_ptr);

	int init_video = TOMB_PROC_PTR<int, int*, int, int, int, int, int, int, int, int, int, int, int, int>(0x004504E8)(&video_ptr, movie_ptr, movieX, movieY, 0, something3, 0, 0, 640, 480, 0, 1, something2);
	int init_playback = TOMB_PROC_PTR<int, HWND, int, int, int>(0x004504E2)(TOMB_GLOBAL(0x00463600, HWND), video_ptr, 1, 0);
		
	if (!init_video && !init_playback) {
		int sound_prec = TOMB_PROC_PTR<int, int>(0x004504DC)(movie_ptr);
		int sound_rate = TOMB_PROC_PTR<int, int>(0x004504D6)(movie_ptr);
		int sound_channel = TOMB_PROC_PTR<int, int>(0x004504D0)(movie_ptr);
		int init_sound = TOMB_PROC_PTR<int, int*, int, int, int, int, int, int, int, int>(0x004504CA)(&sound_ptr, 44100, 1, 1, 22050, sound_channel, sound_rate, sound_prec, 2);
		
		if (TOMB_GLOBAL(0x00456688, int) || (sound_prec, sound_rate, sound_channel, !init_sound)) {
			int init_playback = TOMB_PROC_PTR<int, int, int, int>(0x004504C4)(movie_ptr, video_ptr, sound_ptr);
			int map_video = TOMB_PROC_PTR<int, int, int>(0x004504BE)(video_ptr, 0);
				
			if (!init_playback && !map_video) {
				frames = TOMB_PROC_PTR<int, int>(0x004504B8)(movie_ptr);
				int start_timer = TOMB_PROC_PTR<int, int>(0x004504B2)(movie_ptr);

				if (!start_timer) {
					current_frame = frames - 2;

					if (TOMB_PROC_PTR<int, int>(0x004504AC)(movie_ptr) < current_frame) {
						while (!TOMB_PROC_PTR<int, int, int, int, int, int, int, int, int>(0x004504A6)(movie_ptr, video_ptr, sound_ptr, 0, 0, 0, 0, 0)) {
							TOMB_CALLPROC(0x0043D940);
							
							SDL_Event event;
							SDL_PollEvent(&event);
							if (event.type == SDL_KEYDOWN) {
								if (event.key.keysym.sym == SDLK_SPACE) {
									break;
								}
							}

							if (TOMB_PROC_PTR<int, int>(0x004504AC)(movie_ptr) >= current_frame) {
								break;
							}
						}
					}
				}
			}
		}
	}

	TOMB_CALLPROC(0x004504A0);
	TOMB_PROC_PTR<int, int*>(0x0045049A)(&sound_ptr);
	TOMB_PROC_PTR<int, int*>(0x00450494)(&video_ptr);
	TOMB_PROC_PTR<int, int*>(0x0045048E)(&movie_ptr);
	return 1;
}

int draw_menu() {

	int v2 = 0;
	int v8 = 0;
	int v11 = 0;
	int v12 = 0;
	int v14 = 0;
	__int16 v57 = 0;
	__int16 v58 = 0;
	int bottom_text = 0;
	__int16 v42 = 0;
	int v46 = 0;
	int v47 = 0;
	int v49 = 0;
	int v50 = 0;
	int v51 = 0;
	int v52 = 0;
	int v53 = 0;
	int v59 = 0;
	char v64;

	memset(&v58, 0, 0x30);
	memset(&v42, 0, 0x4C);

	if (TOMB_GLOBAL(0x0045A030, int)) {
		std::cout << "CUNT " << TOMB_GLOBAL(0x0045A030, int) << std::endl;
	}

	TOMB_PROC_PTR<void, int>(0x004026D0)(14560);
	//TOMB_PROC_PTR<void, int>(0x6C1E96A0)(11830);

	TOMB_GLOBAL(0x0045632C, int) = 1;
	TOMB_GLOBAL(0x004550A0, int) = 2;

	TOMB_CALLPROC(0x0041F980);
	if (1) {
		TOMB_PROC_PTR<void, int>(0x00416B20)(0);
	}

	TOMB_CALLPROC(0x0042B000);
	TOMB_CALLPROC(0x00438CC0);

	TOMB_PROC_PTR<void, int*, int, int, int, int, short*>(0x00421580)(&bottom_text, 1, TOMB_GLOBAL(0x00456008, int), TOMB_GLOBAL(0x00456004, int), TOMB_GLOBAL(0x0045A04C, int), &v57);
	std::cout << TOMB_GLOBAL(0x00456008, int) << " " << TOMB_GLOBAL(0x00456004, int) << " " << TOMB_GLOBAL(0x0045A04C, int) << std::endl; // 4545888 5 0

	//SDL_Delay(10000);

	TOMB_PROC_PTR<void, int, int, int>(0x0042AA30)(111, 0, 2); // Play sound effect
	TOMB_GLOBAL(0x004550A0, int) = 2;

	while (1) {

		//TOMB_PROC_PTR<void, int*, int>(0x004217A0)(&bottom_text, 24);

		TOMB_CALLPROC(0x0041E550); // Update inputs
		v2 = TOMB_GLOBAL(0x0045EEF4, int);

		if (!v2) {
			TOMB_GLOBAL(0x0045A070, int) = 0;

		}
		 
		TOMB_GLOBAL(0x0045A06C, int) = v2;

		if (TOMB_GLOBAL(0x0045632C, int) != -1 || TOMB_GLOBAL(0x0045EEF4, int) || v2) {
			TOMB_GLOBAL(0x00459F4C, int) = 0;
			TOMB_GLOBAL(0x00459F50, int) = 0;

		}


		for (int x = 0; x < TOMB_GLOBAL(0x004550A0, int); x++) {
			if (TOMB_GLOBAL(0x0045A0B0, int)) {
				if (TOMB_GLOBAL(0x0045A0B4, int)) {
					TOMB_GLOBAL(0x0045A0B4, int) = TOMB_GLOBAL(0x0045A0B4, int) - 1;
				} else {
					TOMB_GLOBAL(0x0045A0B0, int) = 0;
				}
			}
			std::cout << "x: " << x << std::endl;
			//TOMB_PROC_PTR<void, int*>(0x004217D0)(&bottom_text);
		}


		TOMB_PROC_PTR<void, int*, char*>(0x00421700)(&bottom_text, &v64);
		TOMB_PROC_PTR<void, int>(0x00401000)((int)&v64);
		TOMB_PROC_PTR<void, int*>(0x00421760)(&bottom_text);
		TOMB_CALLPROC(0x0042FC60);
		TOMB_CALLPROC(0x00416A60);
		
		TOMB_CALLPROC(0x0043EA01);
		TOMB_PROC_PTR<void, int, int, int>(0x004019A0)(v49, v50, v51);
		TOMB_PROC_PTR<int, int, int, int>(0x00401500)(SHIWORD(v52), v52, v53);


		for (int x = 0; x < v47; TOMB_GLOBAL(0x006CAD14, int) = TOMB_GLOBAL(0x006CAD14, int) - 48) {
			std::cout << "v12 " << TOMB_GLOBAL(0x006CAD14, int) << std::endl;

			v11 = v42 + 4 * x;

			if (x == v47) {
				v12 = v59;

				for (int y = 0; y < TOMB_GLOBAL(0x004550A0, int); ++y) {
					if (v46) {
						TOMB_GLOBAL(0x0068F3A0, int) = 5120;
						v14 = v11 + 30;
						if (v14) {
							if (v14 >= 0) {
								*(WORD *)(v11 + 30) = v14 - 512;
							} else {
								*(WORD *)(v11 + 30) = v14 + 512;
							}
							v12 = v59;
						}

					} else {

					}
				}
			}

			TOMB_CALLPROC(0x0043EA01);
			TOMB_PROC_PTR<void, int, int, int>(0x00401500)(v8, 0, 0);
			TOMB_PROC_PTR<void, int, int, int>(0x004018F0)(0, 0, 0);
			TOMB_PROC_PTR<void, int, int, int>(0x00401500)(0x4000, 22, 0);
			TOMB_PROC_PTR<void, int>(0x0041FB40)(0);

			x++;
		}
		//TOMB_PROC_PTR<void, int>(0x004201D0)(115);

		TOMB_CALLPROC(0x0042B080);
		TOMB_CALLPROC(0x00439B00);
		TOMB_CALLPROC(0x0042FD10);
		int v20 = TOMB_CALLFUNC(0x0042FC70, int); // refresh background
		TOMB_GLOBAL(0x004550A0, int) = v20;
		TOMB_GLOBAL(0x00462D50, int) = v20;


		if (1) {
			TOMB_PROC_PTR<void, int>(0x00416BB0)(0);
		}

		std::cout << TOMB_GLOBAL(0x00455EE0, int) << std::endl;

		TOMB_PROC_PTR<void, int*, int, int, int>(0x00421970)(&bottom_text, 7, 8, 16);
		TOMB_PROC_PTR<void, int*, int>(0x004219A0)(&bottom_text, 0);
		TOMB_PROC_PTR<void, int*, int, int>(0x004219D0)(&bottom_text, -32768, HIWORD(v52) + -32768);
		TOMB_PROC_PTR<void, int*, int>(0x00421A30)(&bottom_text, 0x2000);


		//TOMB_CALLPROC(0x00);
	}

	return 1;
}

int load_atiset() {
	FILE *atiset = fopen("atiset.dat", "rb");

	if (atiset) {
		fread(TOMB_ADDRESS(0x00456334, DWORD), 2u, 1u, atiset);
		fread(TOMB_ADDRESS(0x00456330, WORD), 2u, 1u, atiset);
		fread(TOMB_ADDRESS(TOMB_ADDRESS_CONTROLS, WORD), 2u, 13u, atiset);
		fread(TOMB_ADDRESS(0x0045A240, DWORD), 4u, 1u, atiset);
		fread(TOMB_ADDRESS(0x00459F60, DWORD), 4u, 1u, atiset);
		fread(TOMB_ADDRESS(0x00453560, double), 8u, 1u, atiset);
		fclose(atiset);
		return 1;
	}
	return 0;
}

int init_game() {
	TOMB_GLOBAL(0x00453530, int) = 1;
	TOMB_GLOBAL(0x00456688, int) = 1;
	TOMB_GLOBAL(0x00459F64, int) = 0;
	TOMB_GLOBAL(0x00459F60, int) = 0;
	TOMB_GLOBAL(0x00453558 + 4, double) = 0x3FF00000;
	TOMB_GLOBAL(0x00453560 + 4, double) = 0x3FF00000;
	TOMB_CALLPROC(TOMB_ADDRESS_INIT_HW);
	TOMB_CALLPROC(0x004344D0);
	TOMB_PROC_PTR<void, int, DWORD>(TOMB_ADDRESS_LOAD_SAVE)(0x2964, TOMB_GLOBAL(0x0045B9C0, DWORD));
	load_atiset();

	if (TOMB_GLOBAL(0x00463610, int)) {
		TOMB_GLOBAL(0x00453560, double) = 0x3FF0000000000000;
		TOMB_GLOBAL(0x0045E960, int) = TOMB_GLOBAL(0x0045A240, int);
	}

	TOMB_GLOBAL(0x00459F64, int) = 0;
	TOMB_PROC_PTR<void, int, double>(TOMB_ADDRESS_PREP_PCX)(2, 1.0);
	TOMB_PROC_PTR<int, const char*>(TOMB_ADDRESS_LOAD_PCX)(reinterpret_cast<char*>(0x00456B8C));

	TOMB_CALLPROC(0x00408E41);

	if (TOMB_GLOBAL(0x00463610, int)) {
		TOMB_CALLPROC(0x0040834C);
	}

	play_fmv(9, 1);
	play_fmv(0, 1);

	if (!TOMB_GLOBAL(0x00463610, int)) {
		TOMB_GLOBAL(0x00459F64, int) = -1;
	}

	TOMB_CALLPROC(0x00408368);
	TOMB_GLOBAL(0x0045A034, int) = (int) malloc(0x380000);

	int v2 = TOMB_STATE_MENU;
	int v4 = 0;
	int v5 = 0;

	while (1) {
		switch (v2) {
		case 64: // In game cutscene
			v2 = TOMB_PROC_PTR<int, int>(0x004110A0)(17);
			break;
		case TOMB_STATE_DEMO: // Demo
			std::cout << "Starting demo" << std::endl;
			v2 = TOMB_CALLFUNC(0x00415B70, int);
			break;
		case TOMB_STATE_MENU: // Main menu
			TOMB_CALLPROC(0x00439750);
			TOMB_PROC_PTR<void, int, double, int>(TOMB_ADDRESS_PREP_PCX)(2, 0.0, 0x3FF00000);
			TOMB_PROC_PTR<int, const char*>(TOMB_ADDRESS_LOAD_PCX)(reinterpret_cast<char*>(0x00456B80));
			TOMB_PROC_PTR<int, int>(0x004362A0)(20);
			TOMB_GLOBAL(0x0045A324, int) = 1;
			TOMB_GLOBAL(0x0045B940, int) = 0;
			std::cout << "Drawing main menu" << std::endl;
			draw_menu();
			//TOMB_PROC_PTR<int, int>(0x0041E760)(1);
			TOMB_GLOBAL(0x0045B940, int) = 1;
			TOMB_CALLPROC(0x0041CD10);
			TOMB_CALLPROC(0x00438E40);

			if (TOMB_GLOBAL(0x00459F50, int)) {	// Start demo
				TOMB_GLOBAL(0x00459F50, int) = 0;
				v2 = 192;
			}
			break;
		default: // Start level
			TOMB_CALLPROC(0x004167D0);
			v4 = v2 & 0xFFFFFFC0;
			v5 = v2 & 0x3F;
			std::cout << "v4 " << v4 << " v2 " << v2 << std::endl;

			if (v4 > 64) {
				break;
			} else {
				if (!TOMB_PROC_PTR<int, int>(0x0041D950)(v5)) {
					if (v5 == 20) {
						TOMB_CALLPROC(0x0041E260);
					}
				}
				
				v2 = TOMB_PROC_PTR<int, int>(0x0041D0C0)(v5);
			}
			break;
		}
	}
	return 1;
}
