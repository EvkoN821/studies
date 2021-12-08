//двусвязный список
//формирование
struct list{
	int info;
	list* next, *pred;
};
lis2* inputlist(){
	list*p;
	int x; cin>>x;
	list*h=new list;
	h->info=x;
	h->next=NULL;
	h->pred=NULL;
	p=h;
	cin>>x;
	while(x){
		list*q=new list;
		q->info=x;
		q->next=NULL;
		q->pred=p;
		p->next=q;
		p=q;
		cin>>x;
	}
	return h;
}
int main(){
	list*h=inputlist();
	list*p=h;
	for(p=h;p!=NULL;p=p->next){
		//...
	}
	
	//удаление элементов
	for(p=h->next;p!=NULL;p=p->next)
		if(p->info%2==0){
			p->pred->next=p->next;
			if(p->next!=NULL) p->next->pred=p->pred;
		}
	if(h->info%2==0){
		h=h->next;
		h->pred=NULL;
	}

	//вставка после
 	for(p=h;p!=NULL;p=p->next)
		if(p->info%2==0){
			list*q=new list;
			q->info=x;
			q->next=p->next;
			q->pred=p;
			if(p->next!=NULL) p->next->pred=q;
			p->next=q;
			p=q;
		}

	//вставка до
	for(p=h->next;p!=NULL;p=p->next){
		if(p->info%2==0){
			list*q=new list;
			q->info=x;
			q->next=p
			q->pred=p->pred;
			p->pred->next=q;
			p->pred=q;
			p=q;
		}
	}
	if(h->info%2==0){
		list*q=new list;
		q->info=x;
		q->next=h;
		q->pred=NULL;
		h->pred=q;
		h=q;
	}
}
	