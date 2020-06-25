    #include<bits/stdc++.h>
    using namespace std;
    int main(){
    	/*Idea: Check for each ranking separately
    	* Each must be linked by if statements such if(not high card) then check for pair
    	* Combine all similar ones together, pair and 2 pair; Straight, flush and straight flush
    	* Assign points to each of these possible hands 
    	* Check in this order: Straight flush, flush, straight, four of a kind, 3 of a kind
    	* 2 pairs, pair then high card
    	*/
    	vector<pair<int,char>> hand[2];//One for black and one for white
    	char suit;
    	string card;
    	map<char,int> Tocards;
    	Tocards['2']=0;
    	Tocards['3']=1;
    	Tocards['4']=2;
    	Tocards['5']=3;
    	Tocards['6']=4;
    	Tocards['7']=5;
    	Tocards['8']=6;
    	Tocards['9']=7;
    	Tocards['T']=8;
    	Tocards['J']=9;
    	Tocards['Q']=10;
    	Tocards['K']=11;
    	Tocards['A']=12;
    	while(true){	
    	bool flush[2]={true,true}, straight[2]={true,true},three[2]={false,false};
    	bool four[2]={false,false},two_pair[2]={false,false},pair[2]={false,false};
    	bool straight_flush[2]={false,false}, full_house[2]={false,false};
    	hand[0].clear();
    	hand[1].clear();
    	int points[2]={0,0};
    	int k=0;
    	for(int i=0;i<10;i++){
    	cin>>card;
    	if(cin.eof()){ return 0;  }
    	hand[k].push_back(make_pair(Tocards[card[0]],card[card.length()-1]));
    	if(i==4){k=1;}
    	}
    	sort(hand[0].begin(),hand[0].end());
    	sort(hand[1].begin(),hand[1].end());
    	int val=0;
    	//Check for straight, flush and straight flush
    	for(int i=0;i<2;i++){
    		suit=hand[i][0].second;
    		val=hand[i][0].first;
    		for(int j=1;j<5;j++){
    		if(hand[i][j].second != suit){
    		flush[i]=false;
    		}
    		if(hand[i][j].first == val+1){
    		val++;
    		}else{
    		straight[i]=false;
    		}
    		}
    		if(flush[i] && straight[i]){
    		straight_flush[i]=true;
    		flush[i]=false;
    		straight[i]=false;
    		}
    	}
    	//Check for pairs and same kind 
    	for(int i=0;i<2;i++){
    	vector<int> count(13,0);
    	val=0;
    	int num_pairs=0;
    		for(int j=0;j<5;j++){
    		count[hand[i][j].first]++;
    		}
    		for(int j=0;j<13;j++){
    		if(count[j]==2){
    		num_pairs++;
    		}
    		if(count[j]>val){
    		val=count[j];
    		}
    		}
    		if(num_pairs==1){pair[i]=true;}
    		if(val == 2 && num_pairs==2){
    		two_pair[i]=true;
    		}
    		if(val == 3 ){
    		three[i]=true;
    		}
    		if(val==4){
    		four[i]=true;
    		}
    		if(three[i] && pair[i]){
    		full_house[i]=true;
    		three[i]=false;
    		pair[i]=false;
    		}
    	}
    	if(straight_flush[0] || straight_flush[1]){
    		if(straight_flush[0] && !straight_flush[1]){
    		points[0]=max(9,points[0]);
    		}else{
    		if(straight_flush[1] && !straight_flush[0]){
    		points[1]=max(9,points[1]);
    		}else{
    			if(hand[0][4].first > hand[1][4].first){
    			points[0]=max(9,points[0]);
    			}else{
    			if(hand[0][4].first < hand[1][4].first){
    			points[1]=max(9,points[1]);
    			}
    			}
    		}
    		}
    	}
    	if(four[0] || four[1]){
    		if(four[0] && !four[1]){
    		points[0]=max(8,points[0]);
    		}
    		else{
    		if(four[1] && !four[0]){
    		points[1]=max(points[1],8);
    		}else{
    			if(hand[0][2].first > hand[1][2].first){
    			points[0]=max(8,points[0]);
    			}else{
    			if(hand[0][2].first < hand[1][2].first){
    			points[1]=max(8,points[1]);
    			}
    			}
    		}
    		}
    	}
    	if(full_house[0] || full_house[1]){
    		if(full_house[0] && !full_house[1]){
    		points[0]=max(7,points[0]);
    		}
    		else{
    		if(full_house[1] && !full_house[0]){
    		points[1]=max(points[1],7);
    		}else{
    			if(hand[0][2].first > hand[1][2].first){
    			points[0]=max(7,points[0]);
    			}else{
    			if(hand[0][2].first < hand[1][2].first){
    			points[1]=max(7,points[1]);
    			}
    			}
    		}
    	}
    	}
     
    	if(straight[0] || straight[1]){
    		if(straight[0] && !straight[1]){
    			points[0]=max(5,points[0]);
    		}
    		else{
    		if(straight[1] && !straight[0]){
    			points[1]=max(5,points[1]);
    		}else{
    			if(hand[0][4].first > hand[1][4].first){
    			points[0]=max(5,points[0]);
    			}else{
    			if(hand[0][4].first < hand[1][4].first){
    			points[1]=max(5,points[1]);
    			}
    			}
    		}
    	}
    	}
    	if(flush[0] || flush[1]){
    		if(flush[0] && !flush[1]){
    		points[0]=max(6,points[0]);
    		}else{
    			if(flush[1] && !flush[0]){
    			points[1]=max(6,points[1]);
    			}else{
    			for(int i=4;i>=0;i--){
    				if(hand[0][i].first != hand[1][i].first){
    				if(hand[0][i].first > hand[1][i].first){
    				points[0]=max(6,points[0]);
    				}else{
    				points[1]=max(6,points[1]);
    				}
    				break;
    				}
    			}
    			}
    	}
    	}
    	if(three[0] || three[1]){
    		if(three[0] && !three[1]){
    			points[0]=max(4,points[0]);
    		}
    		else{
    		if(three[1] && !three[0]){
    			points[1]=max(4,points[1]);
    		}else{
    			if(hand[0][2].first > hand[1][2].first){
    			points[0]=max(4,points[0]);
    			}else{
    			if(hand[0][2].first < hand[1][2].first){
    			points[1]=max(4,points[1]);
    			}
    			}
    		}
    	}
    	}
    	if(two_pair[0] || two_pair[1]){
    		if(two_pair[0] && !two_pair[1]){
    			points[0]=max(3,points[0]);
    		}
    		else{
    		if(two_pair[1] && !two_pair[0]){
    			points[1]=max(3,points[1]);
    		}else{
    			int maxim[4]={0,0,0,0};
    			int last_card[2]={-1,-1};
    			for(int i=0;i<2;i++){
    				vector<int> count(13,0);
    				for(int j=0;j<5;j++){
    				count[hand[i][j].first]++;
    				}
    				for(int j=0;j<13;j++){
    				if(count[j]==1){
    				last_card[i]=j;
    				}
    				}
    				int k=i;
    				for(int j=12;j>=0;j--){
    				if(count[j]==2){
    				maxim[k]=j;
    				k=k+2;
    				}
    				}
    			}
    			if(maxim[0] > maxim[1]){
    			points[0]=max(3,points[0]);
    			}else{
    				if(maxim[0] < maxim[1]){
    				points[1]=max(3,points[1]);
    				}else{
    					if(maxim[2] < maxim[3]){
    					points[1]=max(3,points[1]);
    					}else{
    					if(maxim[2] > maxim[3]){
    					points[0]=max(3,points[0]);
    					}else{
    						if(last_card[0] > last_card[1]){
    						points[0]=max(3,points[0]);
    						}else{
    						if(last_card[0] < last_card[1]){
    						points[1]=max(3,points[1]);
    						}
    						}
    					}
    					}
    				}
    				}
    			}
    			}
    	
    	}
    	if(pair[0] || pair[1]){
    		if(pair[0] && !pair[1]){
    		points[0]=max(2,points[0]);
    		}else{
    			if(pair[1] && !pair[0]){
    			points[1]=max(2,points[1]);
    			}else{
    				int maxim[2]={0,0};
    				vector<int> single[2];
    				for(int i=0;i<2;i++){
    					vector<int> count(13,0);
    					for(int j=0;j<5;j++){
    					count[hand[i][j].first]++;
    					}
    					for(int j=0;j<13;j++){
    					if(count[j]==2){
    					maxim[i]=j;
    					}
    					if(count[j]==1){
    					single[i].push_back(j);
    					}
    					}
    				}
    				if(maxim[0] > maxim[1]){
    				points[0]=max(2,points[0]);
    				}else{
    				if(maxim[1] > maxim[0]){
    				points[1]=max(2,points[1]);
    				}else{
    				for(int i=0;i<2;i++){
    				sort(single[i].begin(),single[i].end());
    				}
    				for(int i=2;i>=0;i--){
    				if(single[0][i] != single[1][i]){
    					if(single[0][i] > single[1][i]){
    					points[0]=max(2,points[0]);
    					}else{
    					points[1]=max(points[1],2);
    					}
    					break;
    				}
    				}
    				}
    			}
    		}
    		}
    	}
    	//High card
    	if(!points[0] && !points[1]){
    		for(int j=4;j>=0;j--){
    		if(hand[0][j].first != hand[1][j].first){
    		if(hand[0][j].first > hand[1][j].first){
    			points[0]=max(1,points[0]);
    		}else{
    			points[1]=max(1,points[1]);
    		}
    		break;
    		}
    		}
    	}
    	if(points[0] > points[1]){
    	cout<<"Black wins."<<endl;
    	}else{
    		if(points[0] < points[1]){
    		cout<<"White wins."<<endl;
    		}else{
    		cout<<"Tie."<<endl;
    		}
    	}
    	}
    return 0;
    }