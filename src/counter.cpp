/*
    Hakkapeliitta - A UCI chess engine. Copyright (C) 2013-2015 Mikko Aarnos.

    Hakkapeliitta is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Hakkapeliitta is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Hakkapeliitta. If not, see <http://www.gnu.org/licenses/>.
*/

#include "counter.hpp"
#include <iostream>

CounterMoveTable::CounterMoveTable()
{
    clear();
}

void CounterMoveTable::update(const Board& pos, const Move& move, const Move& opponentMove)
{
    if (opponentMove.empty()) // Last move was a null move
        return;

    const auto prevToSquare = opponentMove.getTo();
    mCounterMoves[pos.getBoard(prevToSquare)][prevToSquare] = move;
}

Move CounterMoveTable::getCounterMove(const Board& pos, const Move& move) const
{
    if (move.empty()) // Same here
        return 0;

    const auto prevToSquare = move.getTo();
    return mCounterMoves[pos.getBoard(prevToSquare)][prevToSquare];
}

void CounterMoveTable::clear()
{
    mCounterMoves.fill({});
}

