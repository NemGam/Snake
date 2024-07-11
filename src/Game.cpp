#include "game.h"
#include "window.h"
#include <SDL2/SDL.h>

namespace snake {

	SDL_Event event;

	Game::Game(const Window& window)
		: window_(window), direction_(1), exit_code_(0), snake_length_(3),
		food_pos_(0),
		head_position_(kGridHeight / 2 * kGridWidth + kGridWidth / 2), is_running_(false), is_aborting_(false)
	{
		score_text_ = std::unique_ptr<Text>(Text::Create(window, window.GetFont("GILB____.TTF", 60), window.GetWidth() - 20, 20, std::to_string(snake_length_), Text::TextAlignment::kRight, { 130, 130, 130, 255 }));
		game_over_text_ = std::unique_ptr<Text>(Text::Create(window, window.GetFont("GILB____.TTF", 40), window.GetWidth() / 2, window.GetHeight() / 2 + 90, "Press 'R' to restart", Text::TextAlignment::kMiddle, { 200, 200, 200, 255 }));
		std::random_device dev;
		random_engine_ = std::mt19937(dev());
	}

	int Game::Run() {
		is_running_ = true;
		is_aborting_ = false;
		if (!Init()) return -1;


		while (is_running_){
			//Handle input
			HandleInput();

			//Check collisions
			CheckSnakeCollisions();

			//Move the snake
			UpdatePosition();

			//Render snake & food
			Render();

			SDL_Delay(132);
		}
		if (is_aborting_) return exit_code_;

		//Render game over text once and wait for input
		game_over_text_->Render();
		SDL_RenderPresent(const_cast<SDL_Renderer*>(window_.GetRenderer()));
		while (exit_code_ == 0) {
			HandleInput();
			SDL_Delay(200);
		}
		return exit_code_;
	}

	
	void Game::Abort(const int code) {
		this->exit_code_ = code;
		this->is_aborting_ = true;
		this->is_running_ = false;
	}

	bool Game::Init() {

		//Filling array of cells to draw later
		for (int i = 0; i < kGridHeight; i++)
		{
			for (int j = 0; j < kGridWidth; j++)
			{
				render_grid_[i * kGridWidth + j] = { kCellSize * j, kCellSize * i, kCellSize, kCellSize };
			}
		}

		snake_poses_[0] = head_position_;
		snake_poses_[1] = head_position_;
		snake_poses_[2] = head_position_;
		SpawnFood();
		return true;
	}

	void Game::Render() const {
		const auto renderer = const_cast<SDL_Renderer*>(window_.GetRenderer());

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Render food
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &render_grid_[food_pos_]);

		//Render snake
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for (int i = 0; i < snake_length_; ++i)
			SDL_RenderFillRect(renderer, &render_grid_[snake_poses_[i]]);


		//Render score
		score_text_->Render();

		SDL_RenderPresent(renderer);
	}


	void Game::HandleInput() {

		bool called_event = false;
		while (SDL_PollEvent(&event_))
		{
			if (called_event) continue;

			switch (event_.type)
			{
			case SDL_QUIT:
				Abort(-1);
				break;

			case SDL_KEYDOWN:
				switch (event_.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
				case SDL_SCANCODE_W:
					if (direction_ == kGridWidth || direction_ == -kGridWidth) break;
					direction_ = -kGridWidth;
					called_event = true;
					break;

				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_D:
					if (direction_ == -1 || direction_ == 1) break;
					direction_ = 1;
					called_event = true;
					break;

				case SDL_SCANCODE_DOWN:
				case SDL_SCANCODE_S:
					if (direction_ == kGridWidth || direction_ == -kGridWidth) break;
					direction_ = kGridWidth;
					called_event = true;
					break;

				case SDL_SCANCODE_LEFT:
				case SDL_SCANCODE_A:
					if (direction_ == -1 || direction_ == 1) break;
					direction_ = -1;
					called_event = true;
					break;

				case SDL_SCANCODE_R:
					Abort(1);
					break;
			case SDL_SCANCODE_ESCAPE:
					Abort(-1);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	void Game::GameOver() {
		is_running_ = false;
	}

	void Game::UpdatePosition() {
		for (int i = snake_length_ - 1; i > 0; --i)
		{
			snake_poses_[i] = snake_poses_[i - 1];
		}
		snake_poses_[0] = head_position_;
		head_position_ += direction_;
	}

	void Game::SpawnFood() {
		//Choose random position until it finds the free one
		do food_pos_ = random_engine_() % kGridArea;
		while (IsCellOccupied(food_pos_));
	}

	bool Game::IsCellOccupied(const int check) const {
		for (int i = 0; i < snake_length_; i++)
		{
			if (check == snake_poses_[i])
			{
				return true;
			}
		}

		return check == head_position_;
	}

	void Game::CheckSnakeCollisions()
	{
		if (head_position_ == food_pos_)
		{
			IncreaseSnake();
		}
		else if (IsCellOccupied(head_position_ + direction_) || 
			(head_position_ + direction_ < 0) || //Checking top border
			(head_position_ + direction_ > kGridArea) || //Checking bottom border
			(head_position_ % kGridWidth == 0 && (head_position_ + direction_) % kGridWidth == kGridWidth - 1) || //Checking left border
			(head_position_ % kGridWidth == kGridWidth - 1 && (head_position_ + direction_) % kGridWidth == 0)) //Checking right border
		{
			GameOver();
		}
	}

	void Game::IncreaseSnake()
	{
		snake_poses_[snake_length_] = snake_poses_[snake_length_ - 1];
		snake_length_++;
		score_text_->SetText(std::to_string(snake_length_));
		SpawnFood();
	}
}
