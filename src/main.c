#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

const char* APP_NAME = "Sandora2";
const char* APP_VERSION = "1.0";

void handle_options(int argc, char* argv[]);
void usage();
void version();

int main(int argc, char* argv[]) {
#if (_DEBUG)
	printf("Starting %s %s\n", APP_NAME, APP_VERSION);
#endif

	handle_options(argc, argv);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	char title[50];
	sprintf(title, "%s %s", APP_NAME, APP_VERSION);

#if (_DEBUG)
	printf("Creating SDL render window\n");
#endif

	SDL_Window* window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		fprintf(stderr, "Failed to create SDL render window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Surface* screen = SDL_GetWindowSurface(window);

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);

	SDL_Delay(2000);

#if (_DEBUG)
	printf("Unloading SDL\n");
#endif

	SDL_DestroyWindow(window);
	SDL_Quit();

#if (_DEBUG)
	printf("Done\n");
#endif

	return EXIT_SUCCESS;
}

void handle_options(int argc, char* argv[]) {
#if (_DEBUG)
	printf("Parsing arguments\n");
#endif

	static int help_flag;
	static int version_flag;

	static struct option long_options[] = {
		{"help", no_argument, &help_flag, 1},
		{"version", no_argument, &version_flag, 1},
		{NULL, 0, NULL, 0}
	};

	int c;

	while (1) {
		int option_index = 0;

		c = getopt_long(argc, argv, "", long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
			case 0: // flags
				break;

			default:
				usage();
				exit(EXIT_FAILURE);
		}
	}

	if (help_flag) {
		usage();
		exit(EXIT_SUCCESS);
	}

	if (version_flag) {
		version();
		exit(EXIT_SUCCESS);
	}

}

void usage() {
	printf("Usage: sandora2 [options]\n");
	printf("Options:\n");
	printf("  --help\t\tDisplay this information.\n");
	printf("  --version\t\tDisplay version information.\n");
}

void version() {
	printf("%s %s\n", APP_NAME, APP_VERSION);
}
