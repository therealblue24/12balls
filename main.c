#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct problem {
	int balls[12];
	int odd_one_out;
	int compares;
} problem;

problem create_problem(int odd_one_out, int weight)
{
	problem p;
	p.compares = 0;
	for(int i = 0; i < 12; i++) {
		p.balls[i] = 1;
	}
	p.odd_one_out = odd_one_out;
	p.balls[odd_one_out] = weight;
	return p;
}

bool verify_solution(problem p, int (*solution)(problem p))
{
	return p.odd_one_out == solution(p);
}

int weigh_balls(problem p, int *balls, int count)
{
	int ret = 0;
	for(int i = 0; i < count; i++) {
		ret += p.balls[balls[i]];
	}
	return ret;
}

int compare1(problem p, int ball_a, int ball_b)
{
	p.compares++;
	return p.balls[ball_a] - p.balls[ball_b];
}

int compareN(problem p, int *balls_a, int count_a, int *balls_b, int count_b)
{
	p.compares++;
	int a = weigh_balls(p, balls_a, count_a);
	int b = weigh_balls(p, balls_b, count_b);
	return a - b;
}

int solution_4cmp(problem p)
{
	int range0[4] = { 0, 1, 2, 3 };
	int range1[4] = { 4, 5, 6, 7 };
	int range2[4] = { 8, 9, 10, 11 };
	int search[4];

	int range1_c = compareN(p, range0, 4, range1, 4);
	int range2_c = compareN(p, range0, 4, range2, 4);
	int odd_one_weight = 0;

	if(range1_c == 0) {
		memcpy(search, range2, 4 * sizeof(int));
		if(range2_c > 0)
			odd_one_weight = 0;
		else
			odd_one_weight = 1;
	}

	if(range2_c == 0) {
		memcpy(search, range1, 4 * sizeof(int));
		if(range1_c > 0)
			odd_one_weight = 0;
		else
			odd_one_weight = 1;
	}

	if(range1_c != 0 && range2_c != 0) {
		memcpy(search, range0, 4 * sizeof(int));
		assert(range1_c == range2_c);
		if(range1_c > 0)
			odd_one_weight = 1;
		else
			odd_one_weight = 0;
	}

	int search0[2] = { search[0], search[1] };
	int search1[2] = { search[2], search[3] };
	int search2[2];

	int scmp = compareN(p, search0, 2, search1, 2);

	if(scmp > 0 && odd_one_weight > 0) {
		memcpy(search2, search0, 2 * sizeof(int));
	} else if(scmp < 0 && odd_one_weight > 0) {
		memcpy(search2, search1, 2 * sizeof(int));
	} else if(scmp > 0 && odd_one_weight == 0) {
		memcpy(search2, search1, 2 * sizeof(int));
	} else if(scmp < 0 && odd_one_weight == 0) {
		memcpy(search2, search0, 2 * sizeof(int));
	}

	int s2cmp = compare1(p, search2[0], search2[1]);

	if(s2cmp > 0 && odd_one_weight > 0) {
		return search2[0];
	} else if(s2cmp < 0 && odd_one_weight > 0) {
		return search2[1];
	} else if(s2cmp > 0 && odd_one_weight == 0) {
		return search2[1];
	} else if(s2cmp < 0 && odd_one_weight == 0) {
		return search2[0];
	}

	return -1;
}

bool test_solution(int (*solution)(problem p))
{
	bool ok = true;
	for(int pos = 0; pos < 12; pos++) {
		for(int weight = 0; weight <= 1; weight++) {
			problem p = create_problem(pos, 2 * weight);
			bool sol_ok = verify_solution(p, solution);
			if(!sol_ok) {
				ok = false;
				printf("FAILED: odd=%d, weight=%d\n", pos, weight);
			}
		}
	}
	return ok;
}

int main(void)
{
	printf("%d\n", test_solution(solution_4cmp));
}
