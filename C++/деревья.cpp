//формирование и заполнение
struct tree{
	int info;
	tree* l, *r;
	int lev;
};
void add(tree*t, int x){
	if (x<t->info){
		if(t->l==NULL){
			tree*q=new(tree);
			q->info=x;
			q->l=NULL;
			q->r=NULL;
			q->lev=t->lev+1;
			t->l=q;
		}
		else add(t->l,x);
	else{
		if(t->r==NULL){
			tree*q=new(tree);
			q->info=x;
			q->l=NULL;
			q->r=NULL;
			q->lev=t->lev+1;
			t->r=q;
		}
		else add(t->r,x);
	}
}



/*
if (t->l==NULL && t->r==NULL)   // листья
if (t->l!=NULL || t->r!=NULL)   // нелистья
*/

//сумма элементов на каждом уровне, в a[i] сумма элементов на i-м уровне
void sumlev(int a[100], tree* t){
	if(t!=NULL){
		a[t->lev]+=t->info;
		sumlev(a, t->l);
		sumlev(a, t->r);
	}
}

// сумма элементов дерева
int sum (tree* t){
	if (t!=NULL){
		if (     )
			return t->info + sum(t->l) + sum(t->r);
		return sum(t->l) + sum(t->r);
	}
	return 0;
}

// произведение элементов дерева
int pr (tree* t){
	if (t!=NULL){
		if (     )
			return t->info * pr(t->l) * pr(t->r);
		return pr(t->l) * pr(t->r);
	}
	return 1;
}

// bool 
bool f (tree* t){
	if (t!=NULL){
		if (t->info%5==0 && (t->r!=NULL || t->l!=NULL)     // хотя бы 1 нелист кратен 5
			return 1;
		return f(t->r) || f(t->l);
	}
	return 0;
}

// изменение элементов дерева
void f1 (tree* t){
	if(t!=NULL){
		if (t->info%2!=0) t->info*=2;     // все нечетные элементы увеличить в два раза
		f1(t->l);
		f1(t->r);
	}
}

//поиск макс эл
int max(tree*t){
	if(t->r!=NULL)
		return max(t->r);
	else return t->info;

// вывод первого четного элемента
int perv(tree*t){
	if (t == NULL) return 0;
	if (t->info%2==0) return t->info;
	return perv(t->l);
	return perv(t->r);
}

// вывод дерева
void print (tree *t){
	if(t!=NULL){
		cout<<t->info<<endl;
		print(t->l);
		print(t->r);
	}
}

int main(){
	tree*beg=new tree;
	int x; cin>>x;
	beg->info=x;
	beg->r=NULL; beg->l=NULL; beg->lev=0;
	cin>>x;
	while(x){
		add(beg,x);
		cin>>x;
	}
	//...
}