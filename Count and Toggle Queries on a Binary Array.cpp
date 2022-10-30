
#include<bits/stdc++.h>
using namespace std;
const int MAX = 100000;


int tree[MAX] = {0};

bool lazy[MAX] = {false};


void toggle(int node, int st, int en, int us, int ue)
{

	if (lazy[node])
	{

		lazy[node] = false;
		tree[node] = en - st + 1 - tree[node];


		if (st < en)
		{

			lazy[node<<1] = !lazy[node<<1];
			lazy[1+(node<<1)] = !lazy[1+(node<<1)];
		}
	}

	// out of range
	if (st>en || us > en || ue < st)
		return ;

	// Current segment is fully in range
	if (us<=st && en<=ue)
	{
		// Add the difference to current node
		tree[node] = en-st+1 - tree[node];

		// same logic for checking leaf node or not
		if (st < en)
		{

			lazy[node<<1] = !lazy[node<<1];
			lazy[1+(node<<1)] = !lazy[1+(node<<1)];
		}
		return;
	}


	int mid = (st+en)/2;
	toggle((node<<1), st, mid, us, ue);
	toggle((node<<1)+1, mid+1,en, us, ue);


	if (st < en)
		tree[node] = tree[node<<1] + tree[(node<<1)+1];
}


int countQuery(int node, int st, int en, int qs, int qe)
{

	if (st>en || qs > en || qe < st)
		return 0;


	if (lazy[node])
	{

		lazy[node] = false;
		tree[node] = en-st+1-tree[node];


		if (st<en)
		{

			lazy[node<<1] = !lazy[node<<1];
			lazy[(node<<1)+1] = !lazy[(node<<1)+1];
		}
	}


	if (qs<=st && en<=qe)
		return tree[node];

	int mid = (st+en)/2;
	return countQuery((node<<1), st, mid, qs, qe) +
		countQuery((node<<1)+1, mid+1, en, qs, qe);
}


int main()
{
	int n = 5;
	toggle(1, 0, n-1, 1, 2); // Toggle 1 2
	toggle(1, 0, n-1, 2, 4); // Toggle 2 4

	cout << countQuery(1, 0, n-1, 2, 3) << endl; // Count 2 3

	toggle(1, 0, n-1, 2, 4); // Toggle 2 4

	cout << countQuery(1, 0, n-1, 1, 4) << endl; // Count 1 4

return 0;
}

