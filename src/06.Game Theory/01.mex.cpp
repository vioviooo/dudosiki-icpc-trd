//При смешивании нескольких игр выбираем mex их результатов
//(minimim excluded)
int mex(vector<int>& a) {
	sort(all(a));
	if (a[0] > 0) {
		return 0;
	}
	for (int i = 0; i < a.size() - 1; i++) {
		if (a[i] + 1 < a[i + 1])
			return a[i] + 1;
	}
	return a.back() + 1;
}

//Чтобы определить исход игры, достаточно жестко отксорить все возможные ходы
int allxor(vector<int>& sg) {
	int res = 0;
	for (int i = 0; i < sg.size(); i++) {
		res ^= sg[i];
	}
	return res;
}

//Вывод вектора. Полезная штука
template <typename T>
void cout_vec(vector<T>& x) {
	for (int i = 0; i < x.size(); i++) {
		cout << x[i] << ' ';
	}
	cout << '\n';
}

void solve() {
	int n;
	cin >> n;
	int win = 0;
	for (int i = 0; i < n; i++) {
		int a, k;
		cin >> a >> k;
		win = win ^ (a % (k + 1));
	}
	if (win > 0)
		cout << 1;
	else
		cout << 2;
}