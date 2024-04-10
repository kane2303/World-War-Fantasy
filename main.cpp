#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include<SDL_ttf.h>
#include<bits/stdc++.h>
#include"Button.h"
#include"TextureMange.h"
#include"Engine.h"
#include"Troops.h"
#define gRenderer  Engine::GetInstance()->GetRenderer()
using namespace std;


SDL_Rect base,base2;
//anh cua nut
LTexture Texturebutton;
//bg
LTexture Texturebackground1,Texturebackground2,Pausing;
//Texture cua vat
LTexture BG2,BG3,BGframe;

LTexture TextChange;

void loadMedia();

LButton StartA,StartB,StartC;
LTexture TextStA,TextStB,TextStC;

LButton NextA,NextB;
LTexture TextNxtA,TextNxtB;

LButton TroopsIcon1,TroopsIcon2,TroopsIcon3;
LTexture TextTroopsIcon1,TextTroopsIcon2,TextTroopsIcon3,Textplayergold,Textbootcamp,Textbootcamp2;

LButton Cntbut,Quitbut,Nwgbut;
LTexture TextCntbut,TextQuitbut,TextNwgbut,Textwin,Textlose;

LButton TroopsIcon4,TroopsIcon5,TroopsIcon6,TroopsIcon7;
LTexture TextTroop4,TextTroop5,TextTroop6,TextTroop7;

LButton Ultimate;
LTexture TextUltimate;
int trangthai=0;
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

Mix_Music *gMusic = NULL;
Dot dot;

TTF_Font* gFont = NULL;
void loadMedia()
{
//    gMusic = Mix_LoadMUS( ".wav" );

    Texturebackground2.SetTexture();
    Texturebackground1.loadFromFile("assets/background.jpg");
    Pausing.loadFromFile("assets/pausingscreen.png");
    Textwin.loadFromFile("assets/winning.png");
    Textlose.loadFromFile("assets/losing.png");
    TextChange.loadFromFile("assets/chuyencanh.png");
    TextStA.loadFromFile("assets/mainscreen/playbutton.png");
    TextStB.loadFromFile("assets/mainscreen/resumebutton.png");
    TextStC.loadFromFile("assets/mainscreen/quitbutton.png");

    TextNxtA.loadFromFile("assets/mainscreen/easybutton.png");
    TextNxtB.loadFromFile("assets/mainscreen/hardbutton.png");

    //doi 2
    gFont = TTF_OpenFont( "dpcomic.ttf", 28 );
    BG2.loadFromFile2("assets/bg2.png");
    BGframe.loadFromFile2("assets/BGframe2.png");
    TextTroopsIcon1.loadFromFile2("assets/troopsicon1.png");
    TextTroopsIcon2.loadFromFile2("assets/troopsicon2.png");
    TextTroopsIcon3.loadFromFile2("assets/troopsicon3.png");
    TextCntbut.loadFromFile("assets/continuebutton.png");
    TextQuitbut.loadFromFile("assets/quitbutton.png");
    TextNwgbut.loadFromFile("assets/newgamebutton.png");

    //doi 3
    BG3.loadFromFile("assets/background2.jpg");
    TextTroop4.loadFromFile2("assets/troopsicon4.png");
    TextTroop5.loadFromFile2("assets/troopsicon5.png");
    TextTroop6.loadFromFile2("assets/troopsicon6.png");
    TextTroop7.loadFromFile2("assets/bossicon.png");

    TextUltimate.loadFromFile("assets/ulti.png");
}
void Run_dot()
{
    dot.move();
    camera.x = ( dot.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( dot.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
    if( camera.x < 0 ) camera.x = 0;
    if( camera.y < 0 ) camera.y = 0;
    if( camera.x > MAIN_WIDTH - camera.w ) camera.x = MAIN_WIDTH - camera.w;
    if( camera.y > MAIN_HEIGHT - camera.h ) camera.y = MAIN_HEIGHT - camera.h;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }

    return mTexture != NULL;
}
/**                                                                              start merge                                      **/
/**                                                                              start merge                                      **/
/**                                                                              start merge                                      **/

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd;

int Rand(int l, int r)   // sinh 1 số ngẫu nhiên trong đoạn [l; r]
{
    return l+(1ll*rd()*rd()%(r-l+1) +(r-l+1))%(r-l+1);
}

int frame=0, cntlinh=0;
int cntlinhplayer=0, cntlinhbot=0;
int playergold=200;
bool chedokho=false;
queue<int> binhchungplayer;
const int delays=6;

int binhchungs[]=  {-1,   1,    2,    3,    1,    2,    3,    4,     4,     4   };
int HPs[] =        {-1,   150,  100,  50,   200,  200,  200,  2000,  1500,  3000};
int dames[] =      {-1,   34,   20,   300,  50,   40,   50,   300,   0,     0   };
int SPDatks[] =    {-1,   24,   24,   24,   24,   24,   24,   24,    0,     0   };
int ranges[] =     {-1,   5,    190,  5,    15,   220,  15,   15,    0,     0   };
int SPDs[] =       {-1,   2,    2,    3,    2,    2,    2,    3,     0,     0   };
int costs[]=       {-1,   60,   55,   50,   100,  110,  120,  1500,  0,     0   };
int killrewards[]= {-1,   75,   70,   65,   135,  145,  155,  2000,  0,     0   };

struct Troop{
    LTexture Textt;
    int stt;
    int l, r;
    int id;
    int phe;
    int binhchung;
    int HP;
    int dame;
    int SPDatk;
    int range;
    int SPD;
    int deadframe;
    int attackframe;
    int cooldownframe;
    int cost;
    int killreward;
    int prev;
    int behind;
    bool cursed;
    int thunderframe;

    Troop(){
        stt=0;
        l=0;
        r=0;
        id=0;
        phe=0;
        binhchung=0;
        HP=0;
        dame=0;
        SPDatk=0;
        range=0;
        SPD=0;
        deadframe=0;
        attackframe=0;
        cooldownframe=0;
        cost=0;
        killreward=0;
        prev=-1;
        behind=-1;
        cursed=false;
        thunderframe=0;
    }

    Troop(int idd, int thutu, int phee) {
        stt=thutu;
        if(!phee) {
            l=201;

            if(5<=idd && idd<=6) r=l+45;
            else if(idd==4) r=l+35;
            else if(idd==1) r=l+40;
            else if(idd==2) r=l+55;
            else if(idd==3) r=l+50;
            else r=l+96;

            if(8 <= idd && idd <= 9) {l=0; r=l+200;}
        }
        else {
            r=2999;
            if(5<=idd && idd<=6) l=r-45;
            else if(idd==4) l=r-30;
            else if(idd==1) l=r-40;
            else if(idd==2) l=r-55;
            else if(idd==3) l=r-50;
            else l=r-96;
            if(8 <= idd && idd <= 9) {r=3200; l=r-200;}
        }
        if(idd==7) {
            r=l+140;
        }
        Textt.xx=l;
        id=idd;
        phe=phee;
        binhchung = binhchungs[idd];
        HP = HPs[idd];
        dame = dames[idd];
        SPDatk = SPDatks[idd];
        range = ranges[idd];
        if(!phee) SPD = SPDs[idd];
        else SPD = -SPDs[idd];
        deadframe=0;
        attackframe=0;
        cooldownframe=0;
        cost=costs[idd];
        killreward=killrewards[idd];
        prev=-1;
        behind=-1;
        cursed=0;
        thunderframe=0;
    }
};

vector<Troop> danhsachquan;

bool CreateTroop(int id, int phe=false, bool hard=false) { //nếu là tạo lính cho phe player thì chỉ cần nhập 2 tham số đầu vào do hard mặc định bằng false
    if(phe && cntlinhbot>=8) return false;
    if(!phe && cntlinhplayer>=8) return false;
    if(!phe && playergold<costs[id]) return false;

    Troop linh(id, ++cntlinh, phe);
    if(phe && hard) linh.HP += linh.HP/2;
    if(phe && hard) linh.killreward -= 10;
    if(!phe) playergold -= linh.cost;

    if(phe && id<8) {
        for(int i=danhsachquan.size()-1; i>=0; i--)
            if(danhsachquan[i].phe==1 && danhsachquan[i].id<8) {
//                cout<<"Tao va ket noi thanh cong: "<<danhsachquan[i].stt<<" "<<linh.stt<<"\n";
                linh.prev= danhsachquan[i].stt;
                danhsachquan[i].behind = linh.stt;
                break;
            }
    }

    danhsachquan.push_back(linh);
    if(!phe) binhchungplayer.push(binhchungs[id]);

    if(id!=8 && id!=9) {
        if(phe) cntlinhbot++;
        else cntlinhplayer++;
    }

    return true;
}

void ClearTroop(int thutu) {
    for(int i=0; i<danhsachquan.size(); i++)
        if(danhsachquan[i].stt == thutu) {
            if(danhsachquan[i].phe) {
                cntlinhbot--;
                playergold+=danhsachquan[i].killreward;

                int luul=-1, luur=-1;
                for(int l=i-1; l>=0; l--)
                    if(danhsachquan[l].stt == danhsachquan[i].prev) {
                        luul=l; break;
                    }
                for(int r=i+1; r<danhsachquan.size(); r++)
                    if(danhsachquan[r].stt == danhsachquan[i].behind) {
                        luur=r; break;
                    }
                if(luul!=-1) danhsachquan[luul].behind = danhsachquan[i].behind;
                if(luur!=-1) danhsachquan[luur].prev = danhsachquan[i].prev;
            }
            else {
                binhchungplayer.pop();
                cntlinhplayer--;
            }

            danhsachquan.erase( danhsachquan.begin()+i );
            break;
        }
}


void LoadSprite(LTexture &Textt, string path, int frame, int timedelay, int numsheets, bool flip) {
    if(path != "-1" && !Textt.loadFromFile(path.c_str())) {
        cout<<"Khong mo duoc link sau: "<<path<<"\n";
        exit(0);
    }

    int xsum=Textt.getWidth();
    int ysum=Textt.getHeight();

    if(numsheets == 0) { //nếu không phải objectile thì đầu vào là 0
        numsheets = xsum/ysum;
    }

    SDL_Rect KichThuoc[numsheets+1];
    for(int i=0; i<numsheets; i++) {
        KichThuoc[i].x= i*(xsum/numsheets);
        KichThuoc[i].y= 0;
        KichThuoc[i].w= xsum/numsheets;
        KichThuoc[i].h= ysum;
    }

    SDL_Rect* currentClip = &KichThuoc[ (frame / timedelay)%numsheets ];
    Textt.render( Textt.xx , 0, currentClip, flip );
}

string NumToString(int x) {
    string res="";
    if(x==0) return "0";
    while(x>0) {
        char c='0'+x%10;
        res=c+res;
        x/=10;
    }
    return res;
}

string taolink(int id, string thaotac) {
    string res="TroopSprite/";
    res+=NumToString(id);
    res+='/';
    res+=thaotac;
    res+=".png";
    return res;
}
int EndGame=0;
void WorkBase(Troop &doituong) {
    if(doituong.HP<=0) {
        if(trangthai == 2) {
            if(doituong.phe) EndGame = 1;
            else EndGame = -1;
        }
        if(trangthai == 3) {
            if(doituong.phe) EndGame = 2;
            else EndGame=-1;
        }
    }
    string path=taolink(doituong.id, "Base");
    if(!doituong.Textt.loadFromFile(path.c_str())) {
        cout<<"Khong mo duoc link sau: "<<path<<"\n";
        exit(0);
    }

    SDL_Rect KichThuoc;

    KichThuoc.x= 0;
    KichThuoc.y= 0;
    KichThuoc.w= 200;
    KichThuoc.h= 200;

    SDL_Rect* currentClip = &KichThuoc;

    doituong.Textt.render( doituong.Textt.xx , 0, currentClip, doituong.phe, false );
    return;
}

void tancong(Troop &attacker, Troop &defender) {
    int satthuong=attacker.dame;
    if(attacker.binhchung == 1 && defender.binhchung == 2) satthuong*=2;
    if(attacker.binhchung == 2 && defender.binhchung == 3) satthuong*=2;
    if(attacker.binhchung == 3 && defender.binhchung == 1) satthuong*=2;
    if(attacker.id == 2 && defender.id == 3) satthuong= satthuong/2*3;

    defender.HP -= satthuong;
}

void Work(Troop &doituong) {
    bool EnemyInRange=false;
    for(int i=0; i<danhsachquan.size(); i++) {
        if(danhsachquan[i].phe == doituong.phe) continue;
        if(danhsachquan[i].HP <= 0) continue;
        if( ((abs(doituong.r - danhsachquan[i].l) <= doituong.range) && !doituong.phe )  ||  (( abs(danhsachquan[i].r - doituong.l) <= doituong.range ) && doituong.phe) ) {
            EnemyInRange=true;
            break;
        }
        if( max(danhsachquan[i].l, doituong.l) <= min(danhsachquan[i].r, doituong.r) ) EnemyInRange=true;
    }
    if(doituong.id==3 && doituong.attackframe!=0) EnemyInRange=true;

    bool AllyInFrontOfArcher=false;
    for(int i=0; i<danhsachquan.size(); i++) {
        if(danhsachquan[i].phe != doituong.phe) continue;
        if(danhsachquan[i].stt == doituong.stt) continue;
        if( ( doituong.r < danhsachquan[i].l && !doituong.phe )  ||  (danhsachquan[i].r < doituong.l && doituong.phe) ) {
            AllyInFrontOfArcher=true;
            break;
        }
    }

    int khoangcachcho;
    int deltax=doituong.SPD;

    bool CanMove=true;
    for(int i=0; i<danhsachquan.size(); i++) {
        if(danhsachquan[i].stt == doituong.stt) continue;

        if(doituong.phe==danhsachquan[i].phe)  khoangcachcho=40;
        else if(doituong.id==3) khoangcachcho=0;
        else khoangcachcho=5;

        if( (doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt) || doituong.phe != danhsachquan[i].phe ) {
            if( max(danhsachquan[i].l, doituong.l) <= min(danhsachquan[i].r, doituong.r) ) CanMove=false;

            if( ((abs(doituong.r - danhsachquan[i].l) <= khoangcachcho) && !doituong.phe )  ||  (( abs(danhsachquan[i].r - doituong.l) <= khoangcachcho ) && doituong.phe) ) {
                CanMove=false;
                break;
            }
        }

        if(doituong.id==3) {
            if(doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt && !doituong.phe && danhsachquan[i].id<8)
                if(danhsachquan[i].l - doituong.r - 3 <= khoangcachcho) deltax=2;

            if(doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt && doituong.phe && danhsachquan[i].id<8)
                if(doituong.l - danhsachquan[i].r - 3 <= khoangcachcho) deltax=-2;
        }
    }

//    if(doituong.id==3 && doituong.phe) cout<<doituong.stt<<" "<<EnemyInRange<<" "<<CanMove<<" "<<deltax<<"\n";

    if(doituong.HP <= 0 && !(doituong.id==3 && doituong.attackframe>0)) { //kiểm tra xem có ở ngưỡng máu tử hay không
        if(doituong.deadframe<=6*delays) { //gọi từ 0 -> được 6*delays lần từ 0-47, khi ở 47 thì đã có cộng luôn lên 6*delays để erase đối tượng
            LoadSprite(doituong.Textt, taolink(doituong.id, "Death"), doituong.deadframe, delays, 0, doituong.phe);
            doituong.deadframe++;
            if(doituong.deadframe==6*delays) ClearTroop(doituong.stt);
        }
    }
    else {
        if(EnemyInRange) {
            if(doituong.id==3) { //TH đặc biệt -> tấn công xong die luôn
                if(doituong.attackframe==0) doituong.HP=1;
                if(doituong.attackframe==1) doituong.HP=0;

                LoadSprite(doituong.Textt, taolink(doituong.id, "Attack"), doituong.attackframe, delays, 0, doituong.phe); //vì con cá nổ xong cũng đi luôn -> dùng sài tạm biến attackframe thay biến attackframe
                if(doituong.attackframe==3*delays) {
                    int mn=300, sttdich;
                    for(int i=0; i<danhsachquan.size(); i++)
                        if(danhsachquan[i].stt==doituong.stt) sttdich=i;

                    for(int i=0; i<danhsachquan.size(); i++) {
                        if(danhsachquan[i].phe == doituong.phe) continue;
                        if( abs(doituong.l - danhsachquan[i].l) < mn ) {
                            mn = abs(doituong.l - danhsachquan[i].l);
                            sttdich=i;
                        }
                    }
                    tancong(doituong, danhsachquan[sttdich]);
                }
                doituong.attackframe++;
                if(doituong.attackframe==6*delays) ClearTroop(doituong.stt);
            }
            else if(doituong.attackframe<(6*delays)) { //trong chu trình tấn công -> chạy hoạt ảnh tấn công, tấn công và di chuyển nếu có thể
                if(doituong.id==5 && AllyInFrontOfArcher) LoadSprite(doituong.Textt, taolink(doituong.id, "Attack2"), doituong.attackframe, delays, 0, doituong.phe);
                else LoadSprite(doituong.Textt, taolink(doituong.id, "Attack"), doituong.attackframe, delays, 0, doituong.phe);

                if( doituong.attackframe == (6*delays-1) ) {
                    //xác định kẻ địch gần nhất
                    int mn=1000, sttdich=0;
                    for(int i=0; i<danhsachquan.size(); i++) {
                        if(danhsachquan[i].phe == doituong.phe) continue;
                        if( abs(doituong.l - danhsachquan[i].l) < mn ) {
                            mn = abs(doituong.l - danhsachquan[i].l);
                            sttdich=i;
                        }
                    }
                    tancong(doituong, danhsachquan[sttdich]);
                }

                doituong.attackframe++;
                if(doituong.attackframe==6*delays) doituong.cooldownframe=0;
            }
            else { //không trong đợt tấn công -> tiến tiếp hoặc đứng yên đợi
                if(CanMove) {
                    LoadSprite(doituong.Textt, taolink(doituong.id, "Walk"), frame, delays, 0, doituong.phe);
                    doituong.Textt.xx += deltax;
                    doituong.l += deltax;
                    doituong.r += deltax;
                }
                else LoadSprite(doituong.Textt, taolink(doituong.id, "Idle"), frame, delays, 0, doituong.phe);

                if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
                if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
            }

        }
        else if(CanMove) {
            LoadSprite(doituong.Textt, taolink(doituong.id, "Walk"), frame, delays, 0, doituong.phe);
            doituong.Textt.xx += deltax;
            doituong.l += deltax;
            doituong.r += deltax;

            if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
            if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
        }
        else {
            LoadSprite(doituong.Textt, taolink(doituong.id, "Idle"), frame, delays, 0, doituong.phe);

            if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
            if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
        }
    }
    if(doituong.cursed) {
        LoadSprite(doituong.Textt, taolink(10, "Thunder"), doituong.thunderframe, delays, 0, doituong.phe);
        doituong.thunderframe++;
        if(doituong.thunderframe == 6*delays) {
            doituong.cursed=false;
            doituong.thunderframe=0;
        }
    }
}

void LoadSpriteHero(LTexture &Textt, string path, int frame, int timedelay, int numsheets, bool flip) {
    if(path != "-1" && !Textt.loadFromFile(path.c_str())) {
        cout<<"Khong mo duoc link sau: "<<path<<"\n";
        exit(0);
    }

    int xsum=Textt.getWidth();
    int ysum=Textt.getHeight();

    if(numsheets == 0) { //nếu không phải objectile thì đầu vào là 0
        numsheets = xsum/ysum;
    }

    SDL_Rect KichThuoc[numsheets+1];
    for(int i=0; i<numsheets; i++) {
        KichThuoc[i].x= 120+i*(xsum/numsheets);
        KichThuoc[i].y= 30;
        KichThuoc[i].w= 240;
        KichThuoc[i].h= 240;
    }

    SDL_Rect* currentClip = &KichThuoc[ (frame / timedelay)%numsheets ];
    Textt.render( Textt.xx , 0, currentClip, flip, true);
}

void WorkHero(Troop &doituong) {
    bool EnemyInRange=false;
    for(int i=0; i<danhsachquan.size(); i++) {
        if(danhsachquan[i].phe == doituong.phe) continue;
        if( ((abs(doituong.r - danhsachquan[i].l) <= doituong.range) && !doituong.phe )  ||  (( abs(danhsachquan[i].r - doituong.l) <= doituong.range ) && doituong.phe) ) {
            EnemyInRange=true;
            break;
        }
        if( max(danhsachquan[i].l, doituong.l) <= min(danhsachquan[i].r, doituong.r) ) EnemyInRange=true;
    }

    int khoangcachcho=5;
    int deltax=doituong.SPD;

    bool CanMove=true;
    for(int i=0; i<danhsachquan.size(); i++) {
        if(danhsachquan[i].stt == doituong.stt) continue;

        if( (doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt) || doituong.phe != danhsachquan[i].phe )
            if( max(danhsachquan[i].l, doituong.l) <= min(danhsachquan[i].r, doituong.r) ) CanMove=false;

        if( ((abs(doituong.r - danhsachquan[i].l) <= khoangcachcho) && !doituong.phe )  ||  (( abs(danhsachquan[i].r - doituong.l) <= khoangcachcho ) && doituong.phe) ) {
            CanMove=false;
            break;
        }
        if(doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt)
            if(danhsachquan[i].l - doituong.r - 3 <= khoangcachcho) deltax=2;
    }


    if(doituong.HP <= 0) { //kiểm tra xem có ở ngưỡng máu tử hay không
        if(doituong.deadframe<=6*delays) { //gọi từ 0 -> được 6*delays lần từ 0-47, khi ở 47 thì đã có cộng luôn lên 6*delays để erase đối tượng
            LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Death"), doituong.deadframe, delays, 0, doituong.phe);
            doituong.deadframe++;
            if(doituong.deadframe==6*delays) ClearTroop(doituong.stt);
        }
    }
    else {
        if(EnemyInRange) {
            if(doituong.attackframe<(6*delays)) { //trong chu trình tấn công -> chạy hoạt ảnh tấn công, tấn công và di chuyển nếu có thể
                LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Attack"), doituong.attackframe, delays, 0, doituong.phe);

                if( doituong.attackframe == (6*delays-1) ) {
                    //xác định kẻ địch gần nhất
                    int mn=1000, sttdich=0;
                    for(int i=0; i<danhsachquan.size(); i++) {
                        if(danhsachquan[i].phe == doituong.phe) continue;
                        if( abs(doituong.l - danhsachquan[i].l) < mn ) {
                            mn = abs(doituong.l - danhsachquan[i].l);
                            sttdich=i;
                        }
                    }
                    tancong(doituong, danhsachquan[sttdich]);
                }

                doituong.attackframe++;
                if(doituong.attackframe==6*delays) doituong.cooldownframe=0;
            }
            else { //không trong đợt tấn công -> tiến tiếp hoặc đứng yên đợi
                if(CanMove) {
                    LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Walk"), frame, delays, 0, doituong.phe);
                    doituong.Textt.xx += deltax;
                    doituong.l += deltax;
                    doituong.r += deltax;
                }
                else LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Idle"), frame, delays, 0, doituong.phe);

                if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
                if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
            }

        }
        else if(CanMove) {
            LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Walk"), frame, delays, 0, doituong.phe);
            doituong.Textt.xx += deltax;
            doituong.l += deltax;
            doituong.r += deltax;

            if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
            if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
        }
        else {
            LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Idle"), frame, delays, 0, doituong.phe);

            if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
            if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
        }
    }
}

bool AImove(bool hard, int DoiNha){
    int timesummon=400;
    if(hard || (DoiNha==2) ) timesummon=300;

    int l, r;
    if(DoiNha==2) l=1, r=3;
    else l=4, r=6;

    int id=Rand(l, r);
    if(hard && Rand(1, 2)==1 && !binhchungplayer.empty()) {
        id=1;
        if(DoiNha==3) id=4;

        if(binhchungplayer.front()==1) id+=2;
        if(binhchungplayer.front()==3) id++;
    }

    if(frame%timesummon==0) CreateTroop( id, 1, hard );
}

void SaveData() {
    ofstream fo("data.txt");

    fo<<frame<<" "<<cntlinh<<" "<<cntlinhplayer<<" "<<cntlinhbot<<" "<<playergold<<" "<<trangthai<<" "<<chedokho<<"\n";

    fo<<danhsachquan.size()<<"\n";
    for(int i=0; i<danhsachquan.size(); i++) {
        fo<<danhsachquan[i].stt<<" ";
        fo<<danhsachquan[i].l<<" "<<danhsachquan[i].r<<" ";
        fo<<danhsachquan[i].id<<" ";
        fo<<danhsachquan[i].phe<<" ";
        fo<<danhsachquan[i].binhchung<<" ";
        fo<<danhsachquan[i].HP<<" ";
        fo<<danhsachquan[i].dame<<" ";
        fo<<danhsachquan[i].SPDatk<<" ";
        fo<<danhsachquan[i].range<<" ";
        fo<<danhsachquan[i].SPD<<" ";
        fo<<danhsachquan[i].deadframe<<" ";
        fo<<danhsachquan[i].attackframe<<" ";
        fo<<danhsachquan[i].cooldownframe<<" ";
        fo<<danhsachquan[i].cost<<" ";
        fo<<danhsachquan[i].killreward<<" ";
        fo<<danhsachquan[i].prev<<" ";
        fo<<danhsachquan[i].behind<<" ";
        fo<<danhsachquan[i].cursed<<" ";
        fo<<danhsachquan[i].thunderframe<<" ";
        fo<<"\n";
    }
    danhsachquan.clear();

    fo<<binhchungplayer.size()<<"\n";
    while(!binhchungplayer.empty()) {
        fo<<binhchungplayer.front()<<" ";
        binhchungplayer.pop();
    }

    fo.close();
}

void LoadData() {
    ifstream fi("data.txt");

    fi>>frame>>cntlinh>>cntlinhplayer>>cntlinhbot>>playergold>>trangthai>>chedokho;

    int n;
    fi>>n;
    for(int i=0; i<n; i++) {
        Troop Linh;
        fi>>Linh.stt;
        fi>>Linh.l>>Linh.r;
        fi>>Linh.id;
        fi>>Linh.phe;
        fi>>Linh.binhchung;
        fi>>Linh.HP;
        fi>>Linh.dame;
        fi>>Linh.SPDatk;
        fi>>Linh.range;
        fi>>Linh.SPD;
        fi>>Linh.deadframe;
        fi>>Linh.attackframe;
        fi>>Linh.cooldownframe;
        fi>>Linh.cost;
        fi>>Linh.killreward;
        fi>>Linh.prev;
        fi>>Linh.behind;
        fi>>Linh.cursed;
        fi>>Linh.thunderframe;
        Linh.Textt.xx=Linh.l;
        danhsachquan.push_back(Linh);
    }

    int m;
    fi>>m;
    for(int i=0; i<m; i++) {
        int x;
        fi>>x;
        binhchungplayer.push(x);
    }

    fi.close();
}

void LoadNewData() {
    ifstream fi("newdata.txt");

    fi>>frame>>cntlinh>>cntlinhplayer>>cntlinhbot>>playergold>>trangthai>>chedokho;

    int n;
    fi>>n>>n;

    fi.close();
}

void ClearData() {
    frame=0;
    cntlinh=0;
    cntlinhplayer=0;
    cntlinhbot=0;
    playergold=200;
    danhsachquan.clear();
    while(!binhchungplayer.empty()) {
        binhchungplayer.pop();
    }
}

int ThutuToPos(int thutu) {
    for(int i=0; i<danhsachquan.size(); i++)
        if(danhsachquan[i].stt == thutu) return i;
    return -1;
}

void UltimateSkill() { //ứng dụng thuật toán dijkstra
    if(playergold < 150) return;
    else playergold -= 150;

    int ChosenOne = -1, priovalue=-1;
    for(int i=0; i<danhsachquan.size(); i++)
        if(danhsachquan[i].phe && danhsachquan[i].id<8) {
//            cout<<danhsachquan[i].stt<<" ";
            int score=0, cnt=0;
            int n=danhsachquan.size();
            int dp[ n ];
            for(int j=0; j<n; j++) dp[j]=111105;
            priority_queue<pair<int, int>> q;
            dp[i]=0;
            q.push({-0, i});

            while(!q.empty() && cnt<5) {
                int val = -q.top().first;
                int id = q.top().second;
                q.pop();
                if(val>dp[id]) continue;

                if(danhsachquan[id].HP > 0) {
                    if(danhsachquan[id].HP <= 100-cnt*10) score+=300;
                    else score+= 100-cnt*10;

                    cnt++;
                }

                int pos= ThutuToPos(danhsachquan[id].prev);
                if(pos != -1)
                    if(dp[pos] > dp[id] +abs(danhsachquan[id].l - danhsachquan[pos].l) ) {
                        dp[pos] = dp[id] +abs(danhsachquan[id].l - danhsachquan[pos].l);
                        q.push({-dp[pos], pos});
                    }
                pos= ThutuToPos(danhsachquan[id].behind);
                if(pos != -1)
                    if(dp[pos] > dp[id] +abs(danhsachquan[id].l - danhsachquan[pos].l) ) {
                        dp[pos] = dp[id] +abs(danhsachquan[id].l - danhsachquan[pos].l);
                        q.push({-dp[pos], pos});
                    }
            }

            if(score>priovalue) {
                priovalue=score;
                ChosenOne=i;
            }
        }
//    cout<<"\n";

    //ghi nhan TH toi uu va tan cong linh
    if(ChosenOne !=-1) {
        int cnt=0;
        int n=danhsachquan.size();
        int dp[ n ];
        for(int j=0; j<n; j++) dp[j]=111105;
        priority_queue<pair<int, int>> q;
        dp[ChosenOne]=0;
        q.push({-0, ChosenOne});

        while(!q.empty() && cnt<5) {
            int val = -q.top().first;
            int id = q.top().second;
            q.pop();
            if(val>dp[id]) continue;

//            cout<<danhsachquan[id].stt<<" ";
            if(danhsachquan[id].HP > 0) {
                danhsachquan[id].HP -= 100-cnt*10;
                danhsachquan[id].cursed=true;
                cnt++;
//                cout<<danhsachquan[id].id<<" "<<danhsachquan[id].stt<<"    ";
            }

            int pos= ThutuToPos(danhsachquan[id].prev);
            if(pos != -1)
                if(dp[pos] > dp[id] +abs(danhsachquan[id].l - danhsachquan[pos].l) ) {
                    dp[pos] = dp[id] +abs(danhsachquan[id].l - danhsachquan[pos].l);
                    q.push({-dp[pos], pos});
                }
            pos= ThutuToPos(danhsachquan[id].behind);
            if(pos != -1)
                if(dp[pos] > dp[id] +abs(danhsachquan[id].l - danhsachquan[pos].l) ) {
                    dp[pos] = dp[id] +abs(danhsachquan[id].l - danhsachquan[pos].l);
                    q.push({-dp[pos], pos});
                }
        }
//        cout<<"\n\n";
    }
}
/**                                                                              end merge                                      **/
/**                                                                              end merge                                      **/
/**                                                                              end merge                                      **/

void pre1()
{
    SDL_RenderClear(gRenderer);
    Run_dot();
    Texturebackground2.SetRender();
    SDL_RenderClear(gRenderer);
    BG2.rendermenu(0,0);
    SDL_Color BCcolor= {241,16,24};
    Textbootcamp.loadFromRenderedText( to_string(danhsachquan[0].HP),BCcolor);
    Textbootcamp.rendermenu(45,450);

    Textbootcamp2.loadFromRenderedText( to_string(danhsachquan[1].HP),BCcolor);
    Textbootcamp2.rendermenu(3100,450);

}
void last1()
{
    SDL_SetRenderTarget(gRenderer,nullptr);
    SDL_RenderClear(gRenderer);
    Texturebackground2.rendermenu(0,0,&camera);
    BGframe.rendermenu(0,0);

    SDL_Color goldColor= {255,215,0};
    string getgold= "$ ";
    getgold+=to_string(playergold);
    Textplayergold.loadFromRenderedText( getgold,goldColor);
    Textplayergold.rendermenu(5,25);


    TroopsIcon1.render( &TextTroopsIcon1,200,0,75,75,75);
    TroopsIcon2.render( &TextTroopsIcon2,400,0,75,75,75);
    TroopsIcon3.render( &TextTroopsIcon3,600,0,75,75,75);
    Ultimate.render(    &TextUltimate,1100,0,180,100,100);
}
void pre2()
{
    SDL_RenderClear(gRenderer);
    Run_dot();
    Texturebackground2.SetRender();
    SDL_RenderClear(gRenderer);
    BG3.rendermenu(0,0);
    SDL_Color BCcolor= {241,16,24};
    Textbootcamp.loadFromRenderedText( to_string(danhsachquan[0].HP),BCcolor);
    Textbootcamp.rendermenu(45,450);

    Textbootcamp2.loadFromRenderedText( to_string(danhsachquan[1].HP),BCcolor);
    Textbootcamp2.rendermenu(3100,450);
}
void last2()
{
    SDL_SetRenderTarget(gRenderer,nullptr);
    SDL_RenderClear(gRenderer);
    Texturebackground2.rendermenu(0,0,&camera);
    BGframe.rendermenu(0,0);

    SDL_Color goldColor= {255,215,0};
    string getgold= "$ ";
    getgold+=to_string(playergold);
    Textplayergold.loadFromRenderedText( getgold,goldColor);
    Textplayergold.rendermenu(5,25);

    TroopsIcon4.render( &TextTroop4,200,0,75,75,75);
    TroopsIcon5.render( &TextTroop5,400,0,75,75,75);
    TroopsIcon6.render( &TextTroop6,600,0,75,75,75);
    TroopsIcon7.render( &TextTroop7,800,0,75,75,75);
}

bool paused=0,Lpaused=0;
void Runpause()
{
    SDL_RenderClear(gRenderer);
    Pausing.rendermenu(0,0);
    Cntbut.render( &TextCntbut,400,300,500,100,100);
    Quitbut.render( &TextQuitbut,400,500,500,100,100);
    Nwgbut.render( &TextNwgbut,400,400,500,100,100);
}
void Runend(LTexture &Choosen)
{
    SDL_RenderClear(gRenderer);
    Choosen.rendermenu(0,0);
    Quitbut.render( &TextQuitbut,400,500,500,100,100);
    Nwgbut.render( &TextNwgbut,400,400,500,100,100);
}

int main(int argc,char** argv )
{
    Engine::GetInstance()->Init();
    TTF_Init();
//    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    loadMedia();
    bool quit = false;
    SDL_Event e;
    Mix_PlayMusic( gMusic, -1 );
    while( !quit )
    {


        int trangthaitruoc = trangthai;
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            if(trangthai==0)
            {
                if(StartA.handleEvent(&e)) trangthai = 1;
                if(StartB.handleEvent(&e)) {LoadData();}
                if(StartC.handleEvent(&e)) quit = 1;
            }
            else if( trangthai == 1 )
            {
                if( NextA.handleEvent(&e) || NextB.handleEvent(&e) )
                {
                    if(NextB.handleEvent(&e)) chedokho=1;
                    trangthai = 3;
                }
            }
        }

        if( trangthaitruoc == 0)
        {
            Texturebackground1.rendermenu(0,0);
            StartA.render( &TextStA,490,200,375,90,90);
            StartB.render( &TextStB,490,300,375,90,90);
            StartC.render( &TextStC,490,400,375,90,90);
        }
        if(trangthai == 1)
        {
            Texturebackground1.rendermenu(0,0);
            NextA.render( &TextNxtA,490,200,375,90,90);
            NextB.render( &TextNxtB,490,300,375,90,90);
        }
        if(trangthai == 2)
        {
            CreateTroop(8, 0, chedokho);
            CreateTroop(8, 1, chedokho);
            ///vòng lặp chính đời 2
            bool quit2 = 0;
            int alpha=-300;
            EndGame=0;
            while(!quit2)
            {
                if(quit) break;
                int calling=0;

                while( SDL_PollEvent( &e ) != 0 )
                {
                    if(EndGame == -1)
                    {
                        if(Quitbut.handleEvent(&e)) quit = 1;
                        if(Nwgbut.handleEvent(&e))  {
                            ClearData();
                            LoadNewData();
                            calling=0;
                            paused=0;
                            quit2=1;
                            trangthai=1;
                        }
                    }
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    if(paused)
                    {
                        if(Cntbut.handleEvent(&e)) {paused = 0; LoadData();}
                        if(Quitbut.handleEvent(&e)) quit = 1;
                        if(Nwgbut.handleEvent(&e)) {
                            ClearData();
                            LoadNewData();
                            calling=0;
                            paused=0;
                            quit2=1;
                            trangthai=1;
                        }
                    }

                    dot.handleEvent(e);
                    if(TroopsIcon1.handleEvent(&e)) calling = 1;
                    if(TroopsIcon2.handleEvent(&e)) calling = 2;
                    if(TroopsIcon3.handleEvent(&e)) calling = 3;
                    if(Ultimate.handleEvent(&e)) calling =4;
                    if(e.type == SDL_KEYDOWN)
                    {
                        if(e.key.keysym.sym==SDLK_p)
                        {
                            paused=1;
                            SaveData();
                        }
                    }
                }
                if(EndGame!=0)
                {
                    if(EndGame==-1)
                    {
                        Runend(Textlose);
                    }
                    else {
                        if(alpha+1>255)
                        {
                            alpha=255;
                            ClearData();
                            LoadNewData();
                            calling=0;
                            trangthai=3;
                            quit2=1;
                        }
                        else alpha+=1;
                        TextChange.setAlpha(alpha);
                        TextChange.rendermenu(0,0);
                    }
                }
                else if(!paused && !quit2){
                    pre1();

                    AImove(chedokho, trangthai);
                    if(calling != 0) {
                        if(calling!=4)CreateTroop(calling,0);
                        else UltimateSkill();
                    }

                    for(int i=0; i<danhsachquan.size(); i++)
                    {
                        if(danhsachquan[i].Textt.xx <-100 || danhsachquan[i].Textt.xx >3300) ClearTroop(danhsachquan[i].stt);
                        if(danhsachquan[i].id < 7) Work(danhsachquan[i]);
                        else if(danhsachquan[i].id == 7) WorkHero(danhsachquan[i]);
                        else WorkBase(danhsachquan[i]);
                    }
                    frame++;
                    if(frame%150==0) playergold+=5;
                    last1();
                }
                else if(paused)
                {
                    Runpause();
                }
                Engine::GetInstance()->Render();
            }
        }
        if(trangthai==3)
        {
            ///*** doi 3 ***////
            EndGame=0;
            CreateTroop(9, 0, chedokho);
            CreateTroop(9, 1, chedokho);
            ///vòng lặp chính đời 3
            bool quit3 = 0;

            while(!quit3)
            {
                if(quit) break;
                int calling=0;

                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    if(paused)
                    {
                        if(Cntbut.handleEvent(&e)) {paused = 0; LoadData();}
                        if(Quitbut.handleEvent(&e)) quit = 1;
                        if(Nwgbut.handleEvent(&e)) {
                            ClearData();
                            LoadNewData();
                            calling=0;
                            paused=0;
                            quit3=1;
                            trangthai=1;
                        }
                    }

                    dot.handleEvent(e);
                    if(TroopsIcon4.handleEvent(&e)) calling = 4;
                    if(TroopsIcon5.handleEvent(&e)) calling = 5;
                    if(TroopsIcon6.handleEvent(&e)) calling = 6;
                    if(TroopsIcon7.handleEvent(&e)) calling = 7;
                    if(e.type == SDL_KEYDOWN)
                    {
                        if(e.key.keysym.sym==SDLK_p)
                        {
                            paused=1;
                            SaveData();
                        }
                    }
                    if(EndGame!=0)
                    {
                        if(Quitbut.handleEvent(&e)) quit = 1;
                        if(Nwgbut.handleEvent(&e)) {
                            ClearData();
                            LoadNewData();
                            calling=0;
                            paused=0;
                            quit3=1;
                            trangthai=1;
                        }
                    }
                }
                if(EndGame!=0)
                {
                    if(EndGame==-1) Runend(Textlose);
                    else Runend(Textwin);
                }
                else if(!paused && !quit3){
                    pre2();
                    AImove(chedokho, trangthai);

                    if(calling != 0)
                    {
                        if(calling==11) UltimateSkill();
                        else CreateTroop(calling,0);
                    }
                    //cout<<danhsachquan.size()<<"\n";
                    for(int i=0; i<danhsachquan.size(); i++)
                    {   //if(danhsachquan[i].id==8) cout<<danhsachquan[i].id<<" "<<danhsachquan[i].phe<<" "<<danhsachquan[i].HP<<" "<<danhsachquan[i].stt<<"\n";
                        if(danhsachquan[i].Textt.xx <-100 || danhsachquan[i].Textt.xx >3300) ClearTroop(danhsachquan[i].stt);
                        if(danhsachquan[i].id < 7) Work(danhsachquan[i]);
                        else if(danhsachquan[i].id == 7) WorkHero(danhsachquan[i]);
                        else WorkBase(danhsachquan[i]);
                    }
                    //cout<<"\n";
                    frame++;
                    last2();
                    if(frame%150==0) playergold+=5;
                //    if(frame%1000==0) cout<<frame<<"\n";
                }
                else if(paused) Runpause();

                Engine::GetInstance()->Render();
            }
        }
//
        Engine::GetInstance()->Render();
        SDL_RenderClear(gRenderer);
        if(trangthai!=trangthaitruoc)
        {
            if(trangthai==1)
            {
                TextStA.free();
                TextStB.free();
                TextStC.free();
            }
            else if(trangthai==2)
            {
                Texturebackground1.free();
                TextNxtA.free();
                TextNxtB.free();
            }
        }

    }
    Engine::GetInstance()->Quit();

	Mix_FreeMusic( gMusic );
	gMusic = NULL;

	Mix_Quit();
    return 0;
}
