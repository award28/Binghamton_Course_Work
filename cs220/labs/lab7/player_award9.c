rps player_award9(int round, rps *myhist, rps *opphist) {
	
	static int oR = 0;
	static int oP = 0;
	static int oS = 0;
	rps choice;

	if(round != 0) {
		if(opphist[round-1] == Rock) oR++;
		else if(opphist[round-1] == Scissors) oS++;
		else if(opphist[round-1] == Paper) oP++;
	}

	if(oR == oS && oR == oP) {
		if(round == 0) choice = Paper;
		else if(round % 9 == 0) choice = Scissors;
		else if(round % 6 == 0) choice = Rock;
		else choice = Paper;
	}
	else if(oR < oS && oR < oP) choice = Paper;
	else if(oS < oR && oS < oP) choice = Rock;
	else if(oP < oS && oP < oR) choice = Scissors;
	else if(oR > oS && oR > oP) {
		if(round % 2 == 0) choice = Rock;
		else choice = Scissors;
	}
	else if(oP > oS && oP > oR) {
		if(round % 2 == 0) choice = Paper;
		else choice = Rock;
	}
	else if(oS > oR && oS > oP) {
		if(round % 2 == 0) choice = Paper;
		else choice = Scissors;
	}
	else if(oP == oS && oP > oR) choice = Paper;
	else if(oP == oR && oP > oS) choice = Rock;
	else if(oR == oS && oR > oP) choice = Scissors;

	return choice;
}

register_player(player_award9,"award9");
