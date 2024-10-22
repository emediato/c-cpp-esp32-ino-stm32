
#include <stdio.h>
#include <stdlib.h>

/** Given a string A containing only lowercase characters.
Find the frequencies of the characters in order of their occurrence.

First we can find the order of occurence of characters.
Then find the frequencies of the all the possible characters.
Then create the required array of frequencies in order of occurrences.


 * @input A : String termination by '\0'
 *
 * @Output Integer array. You need to malloc memory, and fill the length in len1
 */
int* solve(char* A, int *len1) {
	char* C = A;
	int size = 0;
	while (*(C++))size++;
	C = A;
	int* hist = malloc(sizeof(int)*('z' - 'a' + 1));
	int i = 0, zeros = 0;
	for (i = 0; i < 'z' - 'a' + 1; i++)hist[i] = 0;

	while (*C) {
		if (hist[*C - 'a'] == 0)zeros++;
		hist[*C - 'a']++;
		C++;
	}

	*len1 = zeros;
	int* res = malloc(sizeof(int)*(zeros));
	int f = 0;
	while (*A) {
		if (hist[*A - 'a'] == -1) {}
		else if (hist[*A - 'a'] > 0) {
			res[f++] = hist[*A - 'a'];
			hist[*A - 'a'] = -1;

		}
		A++;
	}

	return res;
}
/** C++17 **/
vector<int> Solution::solve(string A) {
	assert(1 <= A.size() && A.size() <= 1e5);
	string order = "";
	map<char, int> mp;
	for (char x : A) {
		assert('a' <= x && x <= 'z');
		if (order.find(x) == string::npos) {
			order.push_back(x);
		}
		mp[x]++;
	}
	vector<int> ans;
	for (char x : order) {
		ans.push_back(mp[x]);
	}
	return ans;
}

/**FASTEST
 * @input A : String termination by '\0'
 *
 * @Output Integer array. You need to malloc memory, and fill the length in len1
 */
int* solve(char* A, int *len1) {
	int i = 0;
	int freq[26];
	for (i = 0; i < 26; i++) freq[i] = 0;

	i = 0;
	while (*(A + i))
	{
		freq[*(A + i) - 'a']++;
		i++;
	}

	int j = 0;
	int iArr[i];
	for (j = 0; j < i; j++) iArr[j] = 0;

	i = 0;
	j = 0;
	while (*(A + i))
	{
		if (freq[*(A + i) - 'a'])
		{
			iArr[j] = freq[*(A + i) - 'a'];
			j++;
			freq[*(A + i) - 'a'] = 0;
		}

		i++;
	}

	for (i = 0; i < j; i++)
	{
		printf("%d ", iArr[i]);
	}
}
/** C++17 **/
vector<int> Solution::solve(string A) {
	vector<int>v;
	int l = A.length();
	int c[26] = { 0 };
	for (int i = 0; i < l; i++) {
		c[A[i] - 'a']++;
	}
	for (int i = 0; i < l; i++) {
		if (c[A[i] - 'a'] != 0) {
			v.push_back(c[A[i] - 'a']);
			c[A[i] - 'a'] = 0;
		}

	}
	return v;
}


/**LIGHTWEIGHT
 * @input A : String termination by '\0'
 * 
 * @Output Integer array. You need to malloc memory, and fill the length in len1
 */
int* solve(char* A, int *len) {
	int i;
	int len1 = strlen(A);
	int dp[26] = { 0 };
	for (i = 0; i < len1; i++) {
		int ind = A[i] - 'a';
		dp[ind]++;
	}
	int visited[26] = { 0 };
	int n = 0;
	for (i = 0; i < 26; i++) {
		if (dp[i] > 0) n++;
	}
	int j = 0;
	*len = n;
	int *res = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < len1; i++) {
		int ind = A[i] - 'a';
		if (visited[ind] == 0) {
			visited[ind] = 1;
			res[j] = dp[ind];
			j++;
		}
	}
	return res;
}
/** C++17 **/
vector<int> Solution::solve(string A) {
	int a[26] = { 0 }, i, j, k;
	vector <int > v;
	for (i = 0; i < A.size(); i++)
		a[A[i] - 'a']++;
	for (i = 0; i < A.size(); i++)
	{
		if (a[A[i] - 'a'] != 0)
		{
			v.push_back(a[A[i] - 'a']);
			a[A[i] - 'a'] = 0;
		}
	}
	return v;
}


int main()
{

    // This pointer will hold the
    // base address of the block created
    int* ptr;
    int n, i;

    // Get the number of elements for the array
    printf("Enter number of elements:");
    scanf("%d",&n);
    printf("Entered number of elements: %d\n", n);

    // Dynamically allocate memory using malloc()
    ptr = (int*)malloc(n * sizeof(int));

    // Check if the memory has been successfully
    // allocated by malloc or not
    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else {

        // Memory has been successfully allocated
        printf("Memory successfully allocated using malloc.\n");

        // Get the elements of the array
        for (i = 0; i < n; ++i) {
            ptr[i] = i + 1;
        }

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d, ", ptr[i]);
        }
    }

    return 0;
}


