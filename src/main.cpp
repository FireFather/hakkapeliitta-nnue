#include "defs.hpp"
#include "bitboard.hpp"
#include "magic.hpp"
#include "hash.hpp"
#include "ttable.hpp"
#include "position.hpp"
#include "search.hpp"
#include "time.hpp"
#include "eval.hpp"
#include "uci.hpp"

int main()
{
	cout << "Hakkapeliitta 11114, (C) 2013-2014 Mikko Aarnos" << endl;

	// Initialize the engine.
	initInput();
	initializeBitboards();
	initializeMagics();
	initializeHash();
	initializeEval();
	root.initializeBoardFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    initSearch();
	tt.setSize(1 * 1024 * 1024);
	ptt.setSize(4 * 1024 * 1024);

	// Perft 1-8 correct.
	// root.initializeBoardFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	// Perft 1-5 correct.
	// root.initializeBoardFromFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
	// Perft 1-7 correct
	// root.initializeBoardFromFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
	// Perft 1-6 is correct.
	// root.initializeBoardFromFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq -");
	// Perft 1-3 correct
	// root.initializeBoardFromFEN("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");
	// Perft 1-6 correct
	// root.initializeBoardFromFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");

    uciMainLoop();
	/*
	t.start();
	nodeCount = perft(root, 7);
	t.stop();

	cout << "Nodecount = " << nodeCount << endl;
	cout << "Time(in ms) = " << t.getms() << endl;
	cout << "NPS = " << nodeCount / (t.getms() / 1000.0) << endl;
	*/
	return 0; 
}