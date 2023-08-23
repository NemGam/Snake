#include <iostream>
#include "Game.h"
#include "Window.h"
namespace snake {
	SDL_Event event;

	Game::Game(Window* window)
		: snake_length(3), food_pos(0), exit_code(0), direction(1), head_position(grid_height / 2 * grid_width + grid_width / 2),
		score_text(window, Window::get_font("GILB____.TTF", 60), window->get_width() - 60, 40, std::to_string(snake_length), Text::right, {130, 130, 130, 255}),
		game_over_text(window, Window::get_font("GILB____.TTF", 50), window->get_width() / 2, window->get_height() / 2 + 90, "Press 'R' to restart", Text::middle, { 200, 200, 200, 255 }) {

		std::random_device dev;
		random_engine = std::mt19937(dev());
		this->window = window;
	}

	Game::~Game() = default;

	int Game::run() {
		is_running = true;
		is_aborting = false;
		if (!init()) return -1;


		while (is_running){
			//Handle input
			handle_input();

			//Move the snake
			update_position();

			//Check collisions
			check_snake_collisions();

			//Render snake & food
			render();

			SDL_Delay(132);
		}
		if (is_aborting) return exit_code;

		//Render game over text once and wait for input
		game_over_text.render();
		SDL_RenderPresent(window->get_renderer());
		while (exit_code == 0) {
			handle_input();
			SDL_Delay(200);
		}
		return exit_code;
	}

	
	void Game::abort(const int code) {
		this->exit_code = code;
		this->is_aborting = true;
		this->is_running = false;
	}

	bool Game::init() {

		//Filling array of cells to draw later
		for (int i = 0; i < grid_height; i++)
		{
			for (int j = 0; j < grid_width; j++)
			{
				render_grid[i * grid_width + j] = { cell_size * j, cell_size * i, cell_size, cell_size };
			}
		}

		snake_poses[0] = head_position;
		snake_poses[1] = head_position;
		snake_poses[2] = head_position;
		spawn_food();
		return true;
	}

	void Game::render() const {
		SDL_SetRenderDrawColor(window->get_renderer(), 0, 0, 0, 255);
		SDL_RenderClear(window->get_renderer());
		SDL_SetRenderDrawColor(window->get_renderer(), 255, 255, 255, 255);


		//Render snake
		for (unsigned int i = 0; i < snake_length; i++)
			SDL_RenderFillRect(window->get_renderer(), &render_grid[snake_poses[i]]);

		//Render food
		SDL_SetRenderDrawColor(window->get_renderer(), 0, 255, 0, 255);
		SDL_RenderFillRect(window->get_renderer(), &render_grid[food_pos]);

		//Render score
		score_text.render();

		SDL_RenderPresent(window->get_renderer());
	}


	void Game::handle_input() {

		bool called_event = false;
		while (SDL_PollEvent(&event))
		{
			if (called_event) continue;

			switch (event.type)
			{
			case SDL_QUIT:
				abort(-1);
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
				case SDL_SCANCODE_W:
					if (direction == grid_width || direction == -grid_width) break;
					direction = -grid_width;
					called_event = true;
					break;

				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_D:
					if (direction == -1 || direction == 1) break;
					direction = 1;
					called_event = true;
					break;

				case SDL_SCANCODE_DOWN:
				case SDL_SCANCODE_S:
					if (direction == grid_width || direction == -grid_width) break;
					direction = grid_width;
					called_event = true;
					break;

				case SDL_SCANCODE_LEFT:
				case SDL_SCANCODE_A:
					if (direction == -1 || direction == 1) break;
					direction = -1;
					called_event = true;
					break;

				case SDL_SCANCODE_R:
					abort(1);
					break;
			case SDL_SCANCODE_ESCAPE:
					abort(-1);
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

	void Game::game_over() {
		is_running = false;
	}

	void Game::update_position() {
		for (unsigned int i = snake_length - 1; i > 0; --i)
		{
			snake_poses[i] = snake_poses[i - 1];
		}
		snake_poses[0] = head_position;
		head_position += direction;
	}

	void Game::spawn_food() {
		//Choose random position until it finds the free one
		do food_pos = random_engine() % grid_area;
		while (is_cell_snake(food_pos, true));
	}

	bool Game::is_cell_snake(const unsigned int check, const bool food_check) const {
		for (unsigned int i = 0; i < snake_length; i++)
		{
			if (check == snake_poses[i])
			{
				return true;
			}
		}
		if (food_check) return check == head_position;
		return false;
	}

	void Game::check_snake_collisions()
	{
		if (head_position == food_pos)
		{
			increase_snake();
		}
		else if (is_cell_snake(head_position, false))
			game_over();
		else if ((head_position < 0) || //Checking top border
			(head_position > grid_area) || //Checking bottom border
			abs(static_cast<int>(head_position % grid_width) - static_cast<int>(head_position - direction) % grid_width) == grid_width - 1 || //Checking left border
			(head_position % grid_width == 0 && (head_position - direction) % grid_width == grid_width - 1)) //Checking right border
		{
			game_over();
		}
	}

	void Game::increase_snake()
	{
		snake_poses[snake_length] = snake_poses[snake_length - 1];
		snake_length++;
		score_text.set_text(std::to_string(snake_length));
		spawn_food();
	}
}
