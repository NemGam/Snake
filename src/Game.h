#ifndef GAME_H
#define GAME_H
#include "Text.h"
#include <random>
#include <SDL2/SDL.h>
#pragma region CONSTANTS
constexpr int screen_width = 640;
constexpr int screen_height = 480;
constexpr int cell_size = 16;
constexpr int grid_width = screen_width / cell_size;
constexpr int grid_height = screen_height / cell_size;
constexpr int grid_area = grid_height * grid_width;
#pragma endregion


namespace snake {
	class Game {
	public:

		Game(Window* window);
		~Game();
		int run();

	private:

		Window* window;

		std::mt19937 random_engine; //Randomizer

		SDL_Rect render_grid[grid_area]{}; //Grid of rectangles used to render everything
		SDL_Event event{};

		unsigned int snake_length;
		unsigned int snake_poses[grid_area]{}; //Positions of all snake segments

		unsigned int food_pos;

		int exit_code;

		/// <summary>
		/// W = -GRID_WIDTH.
		/// S = GRID_WIDTH.
		/// A = -1.
		/// D = 1.
		/// </summary>
		int direction;

		unsigned int head_position; 

		bool is_running;
		bool is_aborting;

		
		Text score_text;
		Text game_over_text;

		//Initialize the game
		bool init();

		/**
		 * \brief Stop the game loop and skip final input check
		 * \param code Code to exit with
		 */
		void abort(int code);
		void render() const;
		void handle_input();
		void update_position();
		void spawn_food();

		/**
		 * \brief Checks if given position is occupied by snake
		 * \param check Value to check
		 * \param food_check Is this check called by food_spawn()?
		 * \return True - if cell is occupied by snake, False - if not
		 */
		bool is_cell_snake(unsigned int check, bool food_check = false) const;

		void check_snake_collisions();
		void increase_snake();
		void game_over();
	};
}
#endif