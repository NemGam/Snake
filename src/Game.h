#ifndef GAME_H
#define GAME_H
#include "text.h"
#include <random>
#include <SDL2/SDL.h>

#pragma region CONSTANTS
constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;
constexpr int kCellSize = 16;
constexpr int kGridWidth = kScreenWidth / kCellSize;
constexpr int kGridHeight = kScreenHeight / kCellSize;
constexpr int kGridArea = kGridHeight * kGridWidth;
#pragma endregion


namespace snake {
	class Game {
	public:

		explicit Game(const Window& window);
		Game(Game& g) = delete;
		Game(Game&& g) = delete;
		Game& operator=(Game& g) = delete;
		Game&& operator=(Game&& g) = delete;

		~Game() = default;

		int Run();

	private:
		//Stop the program
		void Abort(int code);

		//Game loop functions
		bool Init();
		void Render() const;
		void HandleInput();
		void UpdatePosition();
		void CheckSnakeCollisions();

		void SpawnFood();
		//Checks if given position is occupied by snake (or food if food_check is set to true)
		bool IsCellOccupied(unsigned int check, bool food_check = false) const;
		void IncreaseSnake();
		void GameOver();


		const Window& window_;

		std::mt19937 random_engine_;

		SDL_Rect render_grid_[kGridArea]{}; //Grid of rectangles used to render everything
		SDL_Event event_{};

		// W = -GRID_WIDTH. S = GRID_WIDTH.
		// A = -1. D = 1.
		int direction_;
		int exit_code_;
		unsigned int snake_length_;
		unsigned int snake_poses_[kGridArea]{}; //Positions of all snake segments
		unsigned int food_pos_;
		unsigned int head_position_; 

		bool is_running_;
		bool is_aborting_;

		std::unique_ptr<Text> score_text_;
		std::unique_ptr<Text> game_over_text_;


		


	};
}
#endif