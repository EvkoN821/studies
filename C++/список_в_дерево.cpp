/* дан однонапр список, удалить все отриц элементы, оставшиеся элементы - в дерево двоичного поиска, 
все элементы которые явл листьями уменьшить в два раза, 
найти сумму четных элементов нелистьев  */

struct list {
	int info;
	list* next;
};
list* inputlist() {
	int x; list* p;
	cin >> x;
	list* h = new list;
	h->info = x;
	h->next = NULL;
	p = h;
	cin >> x;
	while (x) {
		list* q = new list;
		q->info = x;
		q->next = NULL;
		p->next = q;
		p = q;
		cin >> x;
	}
	return h;
}
struct tree {
	int info;
	tree* r, * l;
};
void add(tree* t, int x) {
	if (x < t->info) {
		if (t->l == NULL) {
			tree* q = new tree;
			q->info = x;
			q->l = NULL;
			q->r = NULL;
			t->l = q;
		}
		else add(t->l, x);
			}
		else {
			if (t->r == NULL) {
				tree* q = new tree;
				q->info = x;
				q->l = NULL;
				q->r = NULL;
				t->r = q;
			}
			else add(t->r, x);
		}
		}
void f(tree * t) {
	if (t != NULL) {
		if (t->r == NULL && t->l == NULL) t->info /= 2;
		f(t->r);
		f(t->l);
	}
}
int sum(tree * t) {
	if (t != NULL) {
		if (t->info % 2 == 0 && (t->l != NULL || t->r != NULL))
			return t->info + sum(t->l) + sum(t->r);
		return sum(t->r) + sum(t->l);
	}
	return 0;
}
void print(tree * t) {
	if (t != NULL) {
		cout << t->info << "  ";
		print(t->l);
		print(t->r);
	}
}

int main() {
	list* h = inputlist();
	list* p = h;
	for (; p->next != NULL; ) {
		if (p->next->info < 0) p->next = p->next->next;
		else p = p->next;
	}
	if (h->info < 0)h = h->next;
	tree* beg = new tree;
	p = h;
	beg->info = p->info;
	beg->r = NULL;
	beg->l = NULL;
	for (p = h->next; p != NULL; p = p->next)
		add(beg, p->info);
	f(beg);
	cout << endl<<  "сумма четных нелистьев = " << sum(beg) << endl;
	cout << "итоговое дерево";
	print(beg);
}