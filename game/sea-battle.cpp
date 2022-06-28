#include "game/sea-battle.h"
#include <algorithm>

sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn) {
  return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn) {
  return turn == FIRST_PLAYER ? "First" : "Second";
}

sea_battle_t::sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1,
                           std::shared_ptr<player_interface_t> player2, field_t field2)
    :  player_1(std::move(player1)), player_2(std::move(player2)),
      field_1(std::move(field1)), field_2(std::move(field2)) {}

void sea_battle_t::play() {
  while (true){
    auto player = (get_player_name(actual_turn)=="First") ? player_1 : player_2;
    auto player_field = (get_player_name(actual_turn)=="First") ? field_1 : field_2;
    auto opponent = (get_player_name(actual_turn)=="First") ? player_2 : player_1;
    auto &opponent_field = (get_player_name(actual_turn)=="First") ? field_2 : field_1;

    field_t opponent_field_copy(opponent_field);
    for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
      std::replace(opponent_field_copy[i].begin(), opponent_field_copy[i].end(), field_t::SHIP_CELL, field_t::EMPTY_CELL);
    };
    auto [x,y] = player->make_move(player_field, opponent_field_copy);

    if (not field_t::is_cell_valid(x, y)) {
      player->on_incorrect_move(x, y);
      continue;
    };

    if (opponent_field[x][y] == field_t::HIT_CELL or opponent_field[x][y] == field_t::MISS_CELL) {
      player->on_duplicate_move(x, y);
      continue;
    };

    if (opponent_field[x][y] == field_t::EMPTY_CELL) {
      opponent_field[x][y] = field_t::MISS_CELL;
      player->on_miss(x, y);
      actual_turn = change_turn(actual_turn);
      continue;
    };

    if (opponent_field[x][y] == field_t::SHIP_CELL) {
      opponent_field[x][y] = field_t::HIT_CELL;

      for (const auto [dir_x, dir_y] : field_t::DIRECTIONS) {

        if (field_t::is_cell_valid(x + dir_x, y + dir_y) and
            (opponent_field[x + dir_x][y + dir_y] == field_t::SHIP_CELL or
             (opponent_field[x + dir_x][y + dir_y] == field_t::HIT_CELL))) {

          for (int i = 1; i <= field_t::DIRECTIONS.size(); ++i) {
            int x_shift = x + dir_x * i;
            int y_shift = y + dir_y * i;

            if (field_t::is_cell_valid(x_shift, y_shift)) {
              if (opponent_field[x_shift][y_shift] == field_t::HIT_CELL) {
                continue;
              } else if (opponent_field[x_shift][y_shift] == field_t::SHIP_CELL) {
                player->on_hit(x, y);
                goto outer;
              } else if (opponent_field[x_shift][y_shift] == field_t::EMPTY_CELL or
                         opponent_field[x_shift][y_shift] == field_t::MISS_CELL) {
                break;
              }
            }
          }
        }
      }
      player->on_kill(x, y);
    }

    for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
      if (std::any_of(opponent_field[i].begin(), opponent_field[i].end(),
                      [](char cell) { return cell == field_t::SHIP_CELL; })) {
        goto outer;
      }
    }
    player->on_win();
    opponent->on_lose();
    break;
  outer:
    continue;
  };
}