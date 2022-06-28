#include "players/human-player.h"
std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  output_stream << "Your field:" << std::endl;
  output_stream << my_field << std::endl;
  output_stream << "Enemy's field" << std::endl;
  output_stream << enemy_field << std::endl;
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;

  while (true) {
    std::string human_cell;
    std::getline(input_stream, human_cell);
    for (int x = 0; x < field_t::FIELD_SIZE; x++)
      for (int y = 0; y < field_t::FIELD_SIZE; y++)
        if (cells[x][y] == human_cell) {
          return std::pair{x, y};
        }
    output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
  }
}

void human_player_t::on_incorrect_move(int x, int y) {
  assert(false);
}

void human_player_t::on_duplicate_move(int x, int y) {
  output_stream << cells[x][y] << " DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_miss(int x, int y) {
  output_stream << cells[x][y] << " MISS! Enemy's turn!" << std::endl;
}

void human_player_t::on_hit(int x, int y) {
  output_stream << cells[x][y] << " HIT! Your next move!" << std::endl;
}

void human_player_t::on_kill(int x, int y) {
  output_stream << cells[x][y] << " KILL! Your next move!" << std::endl;
}

void human_player_t::on_win() {
  output_stream << "You WIN!" << std::endl;
}

void human_player_t::on_lose() {
  output_stream << "You LOSE!" << std::endl;
}
