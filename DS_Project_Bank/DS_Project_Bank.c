#include <stdio.h>
#define qsize 1000

typedef struct Customer {
    char name[20]; // 客戶 name
    int arr_time; // 客戶到達銀行时间
    int ser_time; // 客戶完成業務要花多少时间
} Customer;

typedef struct Banksystem {
    int _waitlist[qsize];
    int status;
    int people;
    int cooldowntimer;
} Banksystem;

void output (Customer name,int t,int where){
    printf("%s %d %d\n",name.name,t,where);
}

int min_where (Banksystem name[],int _wd){
    int min = name->people;
    int _try = 0;
    int _re = 0;
    while (_try < _wd){
        if ( name[_try].people<min && name[_try].status == 1 ){
            min = name[_try].people;
            _re = _try;
        }
        _try++;
    }
    return _re;
}

int main() {
    int _mainclock = 0;
    int _wd = 0;
    int nowuser = 0;
    int _input_x = 0;
    int _wich_now_read = 0;
    int _banknum = 20;

    Customer _list[100];
    Banksystem _bank[_banknum];

    //以下為輸入段
    FILE *_in = fopen("input1.txt", "r+");
    fscanf(_in, "%d", &_wd);

    //輸入段-重新定義bank啟用狀態
    int _resetmem = 0;
    while ( _resetmem < _banknum ){
        _bank[_resetmem].status = (_resetmem < _wd ? 1 : 0);
        _resetmem++;
    }
    
    while (fscanf(_in, "%s %d %d", _list[_input_x].name, &_list[_input_x].arr_time, &_list[_input_x].ser_time) != EOF) {
        
        //printf("%s %d %d\n", _list[_input_x].name, _list[_input_x].arr_time, _list[_input_x].ser_time);
        //check input system

        if (_list[_input_x].name[0] != '#' && _list[_input_x].name[0] != '@') {
            nowuser++;
        }
        _input_x++;
    }

    fclose(_in);
    //輸入段結束

    //printf("%d",min_where(_bank,_wd));
    //上為找最小貴寒士
    //output(_list[0],100,101);
    //上為輸出寒士

    //進入時序圈
    while ( nowuser != 0 ){
        
        if ( _list[_wich_now_read].arr_time == _mainclock && _wich_now_read < _input_x){
            if (_list[_wich_now_read].name[0] == '#' ){
                _bank[_list[_wich_now_read].ser_time].status = 0;
                while (_bank[_list[_wich_now_read].ser_time].people > 1){
                    int min = min_where(_bank,_wd);
                    _bank[min].people++;
                    _bank[min]._waitlist[_bank[min].people-1] = _bank[_list[_wich_now_read].ser_time]._waitlist[1];
                    _bank[_list[_wich_now_read].ser_time].people--;
                    //左移陣列
                    int _movearr = 0;
                    //左移陣列
                    while ( _movearr < _bank[_list[_wich_now_read].ser_time].people-1){
                        _bank[_list[_wich_now_read].ser_time]._waitlist[_movearr] = _bank[_list[_wich_now_read].ser_time]._waitlist[_movearr+1];
                        _movearr++;
                    }
                }
            }
            else if (_list[_wich_now_read].name[0] == '@'){
                _bank[_list[_wich_now_read].ser_time].status = 1;
            }
            else {
                int min = min_where(_bank,_wd);
                //printf("min%d\n",min);
                _bank[min].people++;
                _bank[min]._waitlist[_bank[min].people-1] = _wich_now_read;
                if (_bank[min].people == 1){
                    _bank[min].cooldowntimer = _list[ _wich_now_read ].ser_time;
                }
            }
            _wich_now_read++;
        }

        _mainclock++;

        int timmer_check_allbank = 0;
        while (timmer_check_allbank < _wd){
            if ( _bank[timmer_check_allbank].people > 0){
                _bank[timmer_check_allbank].cooldowntimer--;
            }
            
            if (_bank[timmer_check_allbank].cooldowntimer == 0 && _bank[timmer_check_allbank].people != 0){
                output( _list[_bank[timmer_check_allbank]._waitlist[0]],_mainclock,timmer_check_allbank);
                _bank[timmer_check_allbank].people--;
                nowuser--;
                if (_bank[timmer_check_allbank].people > 0){
                    int _movearr = 0;
                    //左移陣列
                    while ( _movearr < _bank[timmer_check_allbank].people){
                        _bank[timmer_check_allbank]._waitlist[_movearr] = _bank[timmer_check_allbank]._waitlist[_movearr+1];
                        _movearr++;
                    }
                    
                    //讀入下一位時間
                    _bank[timmer_check_allbank].cooldowntimer = _list[ _bank[timmer_check_allbank]._waitlist[0] ].ser_time;
                }
            }
            timmer_check_allbank ++;
        }

    }
}