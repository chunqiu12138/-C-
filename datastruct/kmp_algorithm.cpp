#include<string>
#include<iostream>

using namespace std;

void Fail(string p,int* fail) {
	int j = 0, k = -1;
	fail[0] = -1;
	while (j < p.length()) {
		if(k==-1||p[j]==p[k]){
			j++;
			k++;
			fail[j] = k;
		}
		else k = fail[k];
	}
}

bool Match(string s,string p,int s_start,int p_start,int* s_fail,int* p_fail) {
	int i = s_start, j = p_start;
	for (;j<p.length();i++,j++) {
		if (s[i] != p[j]) {
			*s_fail = i;
			*p_fail = j;
			return false;
		}
	}
	return true;
}

int KMP(string s, string p, int* fail) {
	int s_start = 0, p_start = 0, s_fail, p_fail;
	while(s_start<=s.length()-p.length())
	{
		if (Match(s, p, s_start, p_start, &s_fail, &p_fail))
			return s_start - p_start;
		else {
			p_start = fail[p_fail];
			s_start = s_fail;
			if (p_start = -1) {
				p_start = 0;
				s_start++;
			}
		}
	}
}

int main() {
	string s = "babababaffababccdeababclkjababab";
	string p = "ababccdeababc";
	int* fail = (int*)malloc(p.length() * sizeof("a"));
	Fail(p, fail);
	cout << KMP(s,p,fail);
}