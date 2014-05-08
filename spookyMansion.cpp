#include<cstdlib>
#include<iostream>

#define ROOM 0
#define WALL 1
#define DOOR 2

using namespace std;

struct point{
	int x, y;
};

struct room{
	point tl, bl, br, tr;
	point door;
};

struct roomListNode{
	room key;
	roomListNode* link;
};

class roomList{
	private:
		 roomListNode* head;
		 roomListNode* current;
		 
	public:
		roomList();
		 void add(room target);
		 void printList();
		 void resetCurrent();
		 bool isEmpty();
		 room getCurrent();
};

void divideRoom(room target, roomList& list, int cont);
void copyRoom(room& source, room& target);
void printRoom(room source);
void printPoint(point source);

int seed = 0;

int main (int argc, char** argv){
	room testRoom;
	roomList list;

	for (int i = 0; i < 5; ++i){
	testRoom.tl.x = 0;
	testRoom.tl.y = 0;
	testRoom.bl.x = 0;
	testRoom.bl.y = 39;
	testRoom.br.x = 39;
	testRoom.br.y = 39;
	testRoom.tr.x = 39;
	testRoom.tr.y = 0;
	testRoom.door.x = 5;
	testRoom.door.y = 10;
	
	int grid[200][200];
	for (int i = 0; i < 40; ++i)
	    for(int j = 0; j < 40; ++j)
	            grid[i][j] = ROOM;
	
	divideRoom(testRoom, list, 100);

	list.printList();
	list.resetCurrent();
	while(!list.isEmpty()){
                           testRoom = list.getCurrent();
                           int left = testRoom.tl.x;
                           int right = testRoom.tr.x;
                           int top = testRoom.tl.y;
                           int bottom = testRoom.bl.y;
                           for (int i = left; i < right; ++i){
                               grid[i][top] = WALL;
                               grid[i][bottom] = WALL;
                           }
                           for (int i = 0; i < testRoom.bl.y; ++i){
                               grid[left][i] = WALL;
                               grid[right][i] = WALL;
                           }
                           //cout << "Tracing room in grid" << endl;   
 }
 for (int i = 0; i < 40; ++i){
	    for(int j = 0; j < 40; ++j){
	        if (grid[j][i] == WALL)
               cout << "0";
             else
                 cout << "-";    
             }
         cout << endl;
     }
     cout << endl << endl;
     getchar();
}
    
	return EXIT_SUCCESS;
}

void roomList::add(room target){
	//cout << "Room to add: " << endl;
	//printRoom(target);
	if(head == NULL) {
		//cout << "head null, insert at head" << endl;
		head = new roomListNode;
		copyRoom(target, head->key);
		head->link = NULL;
		//cout << "New node: " << endl;
		//printRoom(head->key);
	}
	else{
		//cout << "insert at tail" << endl;
		roomListNode* cur = head;
		while(cur->link != NULL) cur = cur->link;
		cur->link = new roomListNode;
		copyRoom(target,cur->link->key);
		cur->link->link = NULL;
	}
	return;
}

void roomList::printList(){
	//if (head == NULL) return;
	roomListNode* cur = head;
	int roomNum = 1;
	while(cur != NULL){
		cout << "Room number: " << roomNum << endl;
		/*
		cout << "\tTop Left: " << cur->key.tl.x  << " " << cur->key.tl.y << endl;
		cout << "\tBottom Left: "<< cur->key.bl.x << " " << cur->key.bl.y << endl;
		cout << "\tBottom Right: " << cur->key.br.x << " " << cur->key.br.y << endl;
		cout << "\tTop Right: " << cur->key.tr.x << " " << cur->key.tr.y << endl;
		cout << "\tDoor: " << cur->key.door.x << " " << cur->key.door.y << endl;
		*/
		printRoom(cur->key);
		++roomNum;
		cur = cur->link;
	}
	return;
}

roomList::roomList() : head(NULL){};

void divideRoom(room target, roomList& list, int cont){
     srand(seed);
     seed = (seed + 7) % 1000000;
	if (rand() % 100 > cont){
//		cout << "Room added to list" << endl;
		list.add(target);
		return;
	}
//	cout << "dividing room" << endl;
	int mid;
	room* room1, * room2;
	bool vert = false; 
    if ((target.tr.x - target.tl.x)<(target.bl.y - target.tl.y)) vert = true;
//	cout << "Incoming room :" << endl;
//	printRoom(target);
	if (vert){
              srand(seed);
     seed = (seed + 7) % 1000000;
		mid = rand() % (target.bl.y - target.tl.y) + 1;
		room1 = new room;
		room1->tl.x = target.tl.x;
		room1->tl.y = target.tl.y;
		room1->bl.x = target.tl.x;
		room1->bl.y = target.tl.y + mid;
		room1->br.x = target.tr.x;
		room1->br.y = target.tr.y + mid;
		room1->tr.x = target.tr.x;
		room1->tr.y = target.tr.y;
		//room1->door.x = target.tl.x + mid;
		//room1->door.y = target.tl.y + mid;

		room2 = new room;
		room2->tl.x = target.tl.x;
		room2->tl.y = target.tl.y + mid;
		room2->bl.x = target.bl.x;
		room2->bl.y = target.bl.y;
		room2->br.x = target.br.x;
		room2->br.y = target.br.y;
		room2->tr.x = target.tr.x;
		room2->tr.y = target.tr.y + mid;
		//room2->door.x = target.tl.x + mid;
		//room2->door.y = target.tl.y + mid;

		//cout << "Top room: " << endl;
//		printRoom(*room1);
//		cout << "Bottom room: " << endl;
//		printRoom(*room2);

		divideRoom(*room1, list, cont - 20);
		divideRoom(*room2, list, cont - 20);
	}
	else {
         srand(seed);
     seed = (seed + 7) % 1000000;
		mid = rand() % (target.tr.x - target.tl.x) + 1;
		room1 = new room;
		room1->tl.x = target.tl.x;
		room1->tl.y = target.tl.y;
		room1->bl.x = target.bl.x;
		room1->bl.y = target.bl.y;
		room1->br.x = target.bl.x + mid;
		room1->br.y = target.br.y;
		room1->tr.x = target.tl.x + mid;
		room1->tr.y = target.tr.y;
		room1->door.x = target.tl.x + mid;
		room1->door.y = target.tl.y + mid;

		room2 = new room;
		room2->tl.x = target.tl.x + mid;
		room2->tl.y = target.tl.y;
		room2->bl.x = target.bl.x + mid;
		room2->bl.y = target.bl.y;
		room2->br.x = target.br.x;
		room2->br.y = target.br.y;
		room2->tr.x = target.tr.x;
		room2->tr.y = target.tr.y;
		room2->door.x = target.tl.x + mid;
		room2->door.y = target.tl.y + mid;

//		cout << "Left room: " << endl;
//		printRoom(*room1);
//		cout << "Right room: " << endl;
//		printRoom(*room2);

		divideRoom(*room1, list, cont - 20);
		divideRoom(*room2, list, cont - 20);
	}
}

void roomList::resetCurrent(){
     current = head;
     return;
}

bool roomList::isEmpty(){
     return current == NULL;
}

room roomList::getCurrent(){
     room retVal;
     copyRoom(current->key, retVal);
     current = current->link;
     return retVal;
}

void copyRoom(room& source, room& target){
//	cout << "source to copy: " << endl;
	//printRoom(source);
	target.tl.x = source.tl.x;
	target.tl.y = source.tl.y;
	target.bl.x = source.bl.x;
	target.bl.y = source.bl.y;
	target.br.x = source.br.x;
	target.br.y = source.br.y;
	target.tr.x = source.tr.x;
	target.tr.y = source.tr.y;
//	cout << "target of copy: " << endl;
	//printRoom(target);
	return;
}

void printRoom(room source){
	printPoint(source.tl);
	printPoint(source.bl);
	printPoint(source.br);
	printPoint(source.tr);
	//cout << "Door: ";
	//printPoint(source.door);
	return;
}

void printPoint(point source){
	cout << "X: " << source.x;
	cout << " Y: " << source.y << endl;
	return;
}
