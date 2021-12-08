//однонапр список
//формирование
struct list{
	int info;
	list* next;
};
list* inputlist(){
	list*h=new list;
	list*p;
	int x; cin>>x;
	h->info=x;
	h->next=NULL;
	p=h;
	cin>>x;
	while(x){
		list* q=new list;
		q->info=x;
		q->next=NULL;
		p->next=q;
		p=q;
		cin>>x;
	}
	return h;
}

int main(){
	list*h=inputlist();
	list*p=h;
	for(p=h; p!=NULL;p=p->next){
		//...
	}
	


	//удаление элемента
	for(p=h;p!=NULL;){
		if(p->next->info%2==0) p->next=p->next->next;
		else p=p->next;
	}
	if(h->info%2==0) h=h->next;
	
	
	//вставка после
 	for(p=h;p!=NULL;p=p->next)
		if(p->info%2==0){
			list*q=new list;
			int x; cin>>x;
			q->info=x;
			q->next=p->next;
			p->next=q;
			p=q;
		}
	
	//вставка до
	for(p=h;p!=NULL;p=p->next){
		if(p->next->info%2==0){
			list*q=new list;
			int x; cin>>x;
			q->info=x;
			q->next=p->next;
			p->next=q;
			p=q;
		}
	}
	if(h->info%2==0){
		list*q=new list;
		q->info=x;
		q->next=h;
		h=q;
	}	
}
