#pragma once

#include <iostream>
#include <cassert>

#include "players/player-interface.h"

class human_player_t : public player_interface_t {
public:
  human_player_t(std::istream &input_stream, std::ostream &output_stream)
      : input_stream(input_stream), output_stream(output_stream) {}

  std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;

  void on_incorrect_move(int x, int y) override;
  void on_duplicate_move(int x, int y) override;
  void on_miss(int x, int y) override;
  void on_hit(int x, int y) override;
  void on_kill(int x, int y) override;

  void on_win() override;
  void on_lose() override;

private:
  std::istream &input_stream;
  std::ostream &output_stream;
  std::string cells[field_t::FIELD_SIZE][field_t::FIELD_SIZE] = {{"1A", "1B", "1C", "1D", "1E", "1F", "1G", "1H", "1I", "1J"},
                               {"2A", "2B", "2C", "2D", "2E", "2F", "2G", "2H", "2I", "2J"},
                               {"3A", "3B", "3C", "3D", "3E", "3F", "3G", "3H", "3I", "3J"},
                               {"4A", "4B", "4C", "4D", "4E", "4F", "4G", "4H", "4I", "4J"},
                               {"5A", "5B", "5C", "5D", "5E", "5F", "5G", "5H", "5I", "5J"},
                               {"6A", "6B", "6C", "6D", "6E", "6F", "6G", "6H", "6I", "6J"},
                               {"7A", "7B", "7C", "7D", "7E", "7F", "7G", "7H", "7I", "7J"},
                               {"8A", "8B", "8C", "8D", "8E", "8F", "8G", "8H", "8I", "8J"},
                               {"9A", "9B", "9C", "9D", "9E", "9F", "9G", "9H", "9I", "9J"},
                               {"10A", "10B", "10C", "10D", "10E", "10F", "10G", "10H", "10I", "10J"}};
};
