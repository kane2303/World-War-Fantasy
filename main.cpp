#include <SDL.h>
#include <SDL_image.h>
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
LTexture TextCntbut,TextQuitbut,TextNwgbut;
int trangthai=0;
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

Dot dot;

TTF_Font* gFont = NULL;
void loadMedia()
{
    Texturebackground2.SetTexture();
    Texturebackground1.loadFromFile("assets/background.jpg");
    Pausing.loadFromFile("assets/pausingscreen.png");
    TextStA.loadFromFile("assets/mainscreen/playbutton.png");
    TextStB.loadFromFile("assets/mainscreen/resumebutton.png");
    TextStC.loadFromFile("assets/mainscreen/quitbutton.png");

    TextNxtA.loadFromFile("assets/mainscreen/easybutton.png");
    TextNxtB.loadFromFile("assets/mainscreen/hardbutton.png");

    //doi 2
    gFont = TTF_OpenFont( "dpcomic.ttf", 28 );
    BG2.loadFromFile("assets/bg.png");
    BGframe.loadFromFile("assets/BGframe.png");
    TextTroopsIcon1.loadFromFile("assets/troopsicon1.png");
    TextTroopsIcon2.loadFromFile("assets/troopsicon2.png");
    TextTroopsIcon3.loadFromFile("assets/troopsicon3.png");
    TextChange.loadFromFile("assets/chuyencanh.png");
    TextCntbut.loadFromFile("assets/continuebutton.png");
    TextQuitbut.loadFromFile("assets/quitbutton.png");
    TextNwgbut.loadFromFile("assets/newgamebutton.png");

    //doi 3
    BG3.loadFromFile("assets/background2.jpg");
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
const int delays=7;

int binhchungs[]=  {-1,   1,    2,    3,    1,    2,    3,    4,     4,     4   };
int HPs[] =        {-1,   150,  100,  50,   200,  200,  200,  2000,  3000,  5000};
int dames[] =      {-1,   34,   20,   300,  50,   40,   50,   300,   0,     0   };
int SPDatks[] =    {-1,   24,   24,   24,   24,   24,   24,   24,    0,     0   };
int ranges[] =     {-1,   5,    190,  5,    15,   220,  15,   15,    0,     0   };
int SPDs[] =       {-1,   2,    2,    3,    2,    2,    2,    3,     0,     0   };
int costs[]=       {-1,   60,   55,   50,   100,  110,  120,  1500,  0,     0   };
int killrewards[]= {-1,   75,   70,   65,   135,  145,  155,  2000,  0,     0   };

struct Troop
{
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

    Troop()
    {
        int stt=0;
        int l=0;
        int r=0;
        int id=0;
        int phe=0;
        int binhchung=0;
        int HP=0;
        int dame=0;
        int SPDatk=0;
        int range=0;
        int SPD=0;
        int deadframe=0;
        int attackframe=0;
        int cooldownframe=0;
        int cost=0;
        int killreward=0;
    }

    Troop(int idd, int thutu, int phee)
    {
        stt=thutu;
        if(!phee)
        {
            l=201;

            if(5<=idd && idd<=6) r=l+45;
            else if(idd==4) r=l+35;
            else if(idd==1) r=l+40;
            else if(idd==2) r=l+55;
            else if(idd==3) r=l+50;
            else r=l+96;

            if(8 <= idd && idd <= 9)
            {
                l=0;
                r=l+200;
            }
        }
        else
        {
            r=2999;
            if(5<=idd && idd<=6) l=r-45;
            else if(idd==4) l=r-30;
            else if(idd==1) l=r-40;
            else if(idd==2) l=r-55;
            else if(idd==3) l=r-50;
            else l=r-96;
            if(8 <= idd && idd <= 9)
            {
                r=3200;
                l=r-200;
            }
        }
        if(idd==7)
        {
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
    }
};

vector<Troop> danhsachquan;

bool CreateTroop(int id, int phe=false, bool hard=false)   //nếu là tạo lính cho phe player thì chỉ cần nhập 2 tham số đầu vào do hard mặc định bằng false
{
    if(phe && cntlinhbot>=8) return false;
    if(!phe && cntlinhplayer>=8) return false;
    if(!phe && playergold<costs[id]) return false;

    Troop linh(id, ++cntlinh, phe);
    if(phe && hard) linh.HP += linh.HP/2;
    if(phe && hard) linh.killreward -= 10;
    if(!phe) playergold -= linh.cost;

    danhsachquan.push_back(linh);
    if(!phe) binhchungplayer.push(binhchungs[id]);

    if(id!=8 && id!=9)
    {
        if(phe) cntlinhbot++;
        else cntlinhplayer++;
    }

    return true;
}

void ClearTroop(int thutu)
{
    for(int i=0; i<danhsachquan.size(); i++)
        if(danhsachquan[i].stt == thutu)
        {
            if(danhsachquan[i].phe)
            {
                cntlinhbot--;
                playergold+=danhsachquan[i].killreward;
            }
            else
            {
                binhchungplayer.pop();
                cntlinhplayer--;
            }

            danhsachquan.erase( danhsachquan.begin()+i );
            break;
        }
}


void LoadSprite(LTexture &Textt, string path, int frame, int timedelay, int numsheets, bool flip)
{
    if(path != "-1" && !Textt.loadFromFile(path.c_str()))
    {
        cout<<"Khong mo duoc link sau: "<<path<<"\n";
        exit(0);
    }

    int xsum=Textt.getWidth();
    int ysum=Textt.getHeight();

    if(numsheets == 0)   //nếu không phải objectile thì đầu vào là 0
    {
        numsheets = xsum/ysum;
    }

    SDL_Rect KichThuoc[numsheets+1];
    for(int i=0; i<numsheets; i++)
    {
        KichThuoc[i].x= i*(xsum/numsheets);
        KichThuoc[i].y= 0;
        KichThuoc[i].w= xsum/numsheets;
        KichThuoc[i].h= ysum;
    }

    SDL_Rect* currentClip = &KichThuoc[ (frame / timedelay)%numsheets ];
    Textt.render( Textt.xx, 0, currentClip, flip );
}

string taolink(int id, string thaotac)
{
    string res="TroopSprite/";
    char c='0'+id;
    res+=c;
    res+='/';
    res+=thaotac;
    res+=".png";
    return res;
}

int EndGame=0;
void WorkBase(Troop &doituong)
{
    //xu ly endgame
    if(doituong.HP<=0) {
        if(trangthai == 2) {
            if(doituong.phe) EndGame=1; //move to next stage
            else EndGame=-1; //cout<<"You lose";
        }
        if(trangthai == 3) {
            if(doituong.phe) EndGame=2; //cout<<"You win"
            else EndGame=-1; //cout<<"You lose"
        }
    }

    string path=taolink(doituong.id, "Base");
    if(!doituong.Textt.loadFromFile(path.c_str()))
    {
        cout<<"Khong mo duoc link sau: "<<path<<"\n";
        exit(0);
    }

    SDL_Rect KichThuoc;

    KichThuoc.x= 0;
    KichThuoc.y= 0;
    KichThuoc.w= 200;
    KichThuoc.h= 200;

    SDL_Rect* currentClip = &KichThuoc;

    doituong.Textt.render( doituong.Textt.xx, 0, currentClip, doituong.phe, false );
    return;
}

void tancong(Troop &attacker, Troop &defender)
{
    int satthuong=attacker.dame;
    if(attacker.binhchung == 1 && defender.binhchung == 2) satthuong*=2;
    if(attacker.binhchung == 2 && defender.binhchung == 3) satthuong*=2;
    if(attacker.binhchung == 3 && defender.binhchung == 1) satthuong*=2;
    if(attacker.id == 2 && defender.id == 3) satthuong= satthuong/2*3;

    defender.HP -= satthuong;
}

void Work(Troop &doituong)
{
    bool EnemyInRange=false;
    for(int i=0; i<danhsachquan.size(); i++)
    {
        if(danhsachquan[i].phe == doituong.phe) continue;
        if( ((abs(doituong.r - danhsachquan[i].l) <= doituong.range) && !doituong.phe )  ||  (( abs(danhsachquan[i].r - doituong.l) <= doituong.range ) && doituong.phe) )
        {
            EnemyInRange=true;
            break;
        }
        if( max(danhsachquan[i].l, doituong.l) <= min(danhsachquan[i].r, doituong.r) ) EnemyInRange=true;
    }
    if(doituong.id==3 && doituong.deadframe!=0) EnemyInRange=true;

    bool AllyInFrontOfArcher=false;
    for(int i=0; i<danhsachquan.size(); i++)
    {
        if(danhsachquan[i].phe != doituong.phe) continue;
        if(danhsachquan[i].stt == doituong.stt) continue;
        if( ( doituong.r < danhsachquan[i].l && !doituong.phe )  ||  (danhsachquan[i].r < doituong.l && doituong.phe) )
        {
            AllyInFrontOfArcher=true;
            break;
        }
    }

    int khoangcachcho;
    int deltax=doituong.SPD;

    bool CanMove=true;
    for(int i=0; i<danhsachquan.size(); i++)
    {
        if(danhsachquan[i].stt == doituong.stt) continue;

        if(doituong.phe==danhsachquan[i].phe)  khoangcachcho=40;
        else if(doituong.id==3) khoangcachcho=0;
        else khoangcachcho=5;

        if( (doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt) || doituong.phe != danhsachquan[i].phe )
        {
            if( max(danhsachquan[i].l, doituong.l) <= min(danhsachquan[i].r, doituong.r) ) CanMove=false;

            if( ((abs(doituong.r - danhsachquan[i].l) <= khoangcachcho) && !doituong.phe )  ||  (( abs(danhsachquan[i].r - doituong.l) <= khoangcachcho ) && doituong.phe) )
            {
                CanMove=false;
                break;
            }
        }

        if(doituong.id==3)
        {
            if(doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt && !doituong.phe && danhsachquan[i].id<8)
                if(danhsachquan[i].l - doituong.r - 3 <= khoangcachcho) deltax=2;

            if(doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt && doituong.phe && danhsachquan[i].id<8)
                if(doituong.l - danhsachquan[i].r - 3 <= khoangcachcho) deltax=-2;
        }
    }

//    if(doituong.id==3 && doituong.phe) cout<<doituong.stt<<" "<<EnemyInRange<<" "<<CanMove<<" "<<deltax<<"\n";

    if(doituong.HP <= 0)   //kiểm tra xem có ở ngưỡng máu tử hay không
    {
        if(doituong.deadframe<=6*delays)   //gọi từ 0 -> được 6*delays lần từ 0-47, khi ở 47 thì đã có cộng luôn lên 6*delays để erase đối tượng
        {
            LoadSprite(doituong.Textt, taolink(doituong.id, "Death"), doituong.deadframe, delays, 0, doituong.phe);
            doituong.deadframe++;
            if(doituong.deadframe==6*delays) ClearTroop(doituong.stt);
        }
    }
    else
    {
        if(EnemyInRange)
        {
            if(doituong.id==3)   //TH đặc biệt -> tấn công xong die luôn
            {
                if(doituong.deadframe==0) doituong.HP=2000; //fix đang nổ thì bị pháp sư giết -> cancel đòn nổ
                LoadSprite(doituong.Textt, taolink(doituong.id, "Attack"), doituong.deadframe, delays, 0, doituong.phe); //vì con cá nổ xong cũng đi luôn -> dùng sài tạm biến deadframe thay biến attackframe
                if(doituong.deadframe==3*delays)
                {
                    int mn=80, sttdich;
                    for(int i=0; i<danhsachquan.size(); i++)
                        if(danhsachquan[i].stt==doituong.stt) sttdich=i;

                    for(int i=0; i<danhsachquan.size(); i++)
                    {
                        if(danhsachquan[i].phe == doituong.phe) continue;
                        if( abs(doituong.l - danhsachquan[i].l) < mn )
                        {
                            mn = abs(doituong.l - danhsachquan[i].l);
                            sttdich=i;
                        }
                    }
                    tancong(doituong, danhsachquan[sttdich]);
                }
                doituong.deadframe++;
                if(doituong.deadframe==6*delays) ClearTroop(doituong.stt);
            }
            else if(doituong.attackframe<(6*delays))   //trong chu trình tấn công -> chạy hoạt ảnh tấn công, tấn công và di chuyển nếu có thể
            {
                if(doituong.id==5 && AllyInFrontOfArcher) LoadSprite(doituong.Textt, taolink(doituong.id, "Attack2"), doituong.attackframe, delays, 0, doituong.phe);
                else LoadSprite(doituong.Textt, taolink(doituong.id, "Attack"), doituong.attackframe, delays, 0, doituong.phe);

                if( doituong.attackframe == (6*delays-1) )
                {
                    //xác định kẻ địch gần nhất
                    int mn=1000, sttdich=0;
                    for(int i=0; i<danhsachquan.size(); i++)
                    {
                        if(danhsachquan[i].phe == doituong.phe) continue;
                        if( abs(doituong.l - danhsachquan[i].l) < mn )
                        {
                            mn = abs(doituong.l - danhsachquan[i].l);
                            sttdich=i;
                        }
                    }
                    tancong(doituong, danhsachquan[sttdich]);
                }

                doituong.attackframe++;
                if(doituong.attackframe==6*delays) doituong.cooldownframe=0;
            }
            else   //không trong đợt tấn công -> tiến tiếp hoặc đứng yên đợi
            {
                if(CanMove)
                {
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
        else if(CanMove)
        {
            LoadSprite(doituong.Textt, taolink(doituong.id, "Walk"), frame, delays, 0, doituong.phe);
            doituong.Textt.xx += deltax;
            doituong.l += deltax;
            doituong.r += deltax;

            if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
            if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
        }
        else
        {
            LoadSprite(doituong.Textt, taolink(doituong.id, "Idle"), frame, delays, 0, doituong.phe);

            if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
            if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
        }
    }
}

void LoadSpriteHero(LTexture &Textt, string path, int frame, int timedelay, int numsheets, bool flip)
{
    if(path != "-1" && !Textt.loadFromFile(path.c_str()))
    {
        cout<<"Khong mo duoc link sau: "<<path<<"\n";
        exit(0);
    }

    int xsum=Textt.getWidth();
    int ysum=Textt.getHeight();

    if(numsheets == 0)   //nếu không phải objectile thì đầu vào là 0
    {
        numsheets = xsum/ysum;
    }

    SDL_Rect KichThuoc[numsheets+1];
    for(int i=0; i<numsheets; i++)
    {
        KichThuoc[i].x= 120+i*(xsum/numsheets);
        KichThuoc[i].y= 30;
        KichThuoc[i].w= 240;
        KichThuoc[i].h= 240;
    }

    SDL_Rect* currentClip = &KichThuoc[ (frame / timedelay)%numsheets ];
    Textt.render( Textt.xx, 0, currentClip, flip, true);
}

void WorkHero(Troop &doituong)
{
    bool EnemyInRange=false;
    for(int i=0; i<danhsachquan.size(); i++)
    {
        if(danhsachquan[i].phe == doituong.phe) continue;
        if( ((abs(doituong.r - danhsachquan[i].l) <= doituong.range) && !doituong.phe )  ||  (( abs(danhsachquan[i].r - doituong.l) <= doituong.range ) && doituong.phe) )
        {
            EnemyInRange=true;
            break;
        }
        if( max(danhsachquan[i].l, doituong.l) <= min(danhsachquan[i].r, doituong.r) ) EnemyInRange=true;
    }

    int khoangcachcho=5;
    int deltax=doituong.SPD;

    bool CanMove=true;
    for(int i=0; i<danhsachquan.size(); i++)
    {
        if(danhsachquan[i].stt == doituong.stt) continue;

        if( (doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt) || doituong.phe != danhsachquan[i].phe )
            if( max(danhsachquan[i].l, doituong.l) <= min(danhsachquan[i].r, doituong.r) ) CanMove=false;

        if( ((abs(doituong.r - danhsachquan[i].l) <= khoangcachcho) && !doituong.phe )  ||  (( abs(danhsachquan[i].r - doituong.l) <= khoangcachcho ) && doituong.phe) )
        {
            CanMove=false;
            break;
        }
        if(doituong.phe==danhsachquan[i].phe && danhsachquan[i].stt<doituong.stt)
            if(danhsachquan[i].l - doituong.r - 2 <= khoangcachcho) deltax=1;
    }


    if(doituong.HP <= 0)   //kiểm tra xem có ở ngưỡng máu tử hay không
    {
        if(doituong.deadframe<=6*delays)   //gọi từ 0 -> được 6*delays lần từ 0-47, khi ở 47 thì đã có cộng luôn lên 6*delays để erase đối tượng
        {
            LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Death"), doituong.deadframe, delays, 0, doituong.phe);
            doituong.deadframe++;
            if(doituong.deadframe==6*delays) ClearTroop(doituong.stt);
        }
    }
    else
    {
        if(EnemyInRange)
        {
            if(doituong.attackframe<(6*delays))   //trong chu trình tấn công -> chạy hoạt ảnh tấn công, tấn công và di chuyển nếu có thể
            {
                LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Attack"), doituong.attackframe, delays, 0, doituong.phe);

                if( doituong.attackframe == (6*delays-1) )
                {
                    //xác định kẻ địch gần nhất
                    int mn=1000, sttdich=0;
                    for(int i=0; i<danhsachquan.size(); i++)
                    {
                        if(danhsachquan[i].phe == doituong.phe) continue;
                        if( abs(doituong.l - danhsachquan[i].l) < mn )
                        {
                            mn = abs(doituong.l - danhsachquan[i].l);
                            sttdich=i;
                        }
                    }
                    tancong(doituong, danhsachquan[sttdich]);
                }

                doituong.attackframe++;
                if(doituong.attackframe==6*delays) doituong.cooldownframe=0;
            }
            else   //không trong đợt tấn công -> tiến tiếp hoặc đứng yên đợi
            {
                if(CanMove)
                {
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
        else if(CanMove)
        {
            LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Walk"), frame, delays, 0, doituong.phe);
            doituong.Textt.xx += deltax;
            doituong.l += deltax;
            doituong.r += deltax;

            if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
            if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
        }
        else
        {
            LoadSpriteHero(doituong.Textt, taolink(doituong.id, "Idle"), frame, delays, 0, doituong.phe);

            if(doituong.cooldownframe < 12*delays) doituong.cooldownframe++;
            if(doituong.cooldownframe == 12*delays) doituong.attackframe=0;
        }
    }
}

bool AImove(bool hard, int DoiNha)
{
    int timesummon=400;
    if(hard || (DoiNha==2) ) timesummon=300;

    int l, r;
    if(DoiNha==2) l=1, r=3;
    else l=4, r=6;

    int id=Rand(l, r);
    if(hard && Rand(1, 2)==1 && !binhchungplayer.empty())
    {
        id=1;
        if(DoiNha==3) id=4;

        if(binhchungplayer.front()==1) id+=2;
        if(binhchungplayer.front()==3) id++;
    }

    if(frame%timesummon==0) CreateTroop( id, 1, hard );
}

void SaveData()
{
    ofstream fo("data.txt");

    fo<<frame<<" "<<cntlinh<<" "<<cntlinhplayer<<" "<<cntlinhbot<<" "<<playergold<<" "<<trangthai<<" "<<chedokho<<"\n";

    fo<<danhsachquan.size()<<"\n";
    for(int i=0; i<danhsachquan.size(); i++)
    {
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
        fo<<danhsachquan[i].killreward<<"\n";
    }
    danhsachquan.clear();

    fo<<binhchungplayer.size()<<"\n";
    while(!binhchungplayer.empty())
    {
        fo<<binhchungplayer.front()<<" ";
        binhchungplayer.pop();
    }

    fo.close();
}

void LoadData()
{
    ifstream fi("data.txt");

    fi>>frame>>cntlinh>>cntlinhplayer>>cntlinhbot>>playergold>>trangthai>>chedokho;

    int n;
    fi>>n;
    for(int i=0; i<n; i++)
    {
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
        Linh.Textt.xx=Linh.l;
        danhsachquan.push_back(Linh);
    }

    int m;
    fi>>m;
    for(int i=0; i<m; i++)
    {
        int x;
        fi>>x;
        binhchungplayer.push(x);
    }

    fi.close();
}

/**                                                                              end merge                                      **/
/**                                                                              end merge                                      **/
/**                                                                              end merge                                      **/
int dengiolendoi=0,alpha=0;
void pre1()
{
    SDL_RenderClear(gRenderer);
    Run_dot();
    Texturebackground2.SetRender();
    SDL_RenderClear(gRenderer);
    BG2.rendermenu(0,0);
    SDL_Rect tmp{0,0,200,200};
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

    SDL_Color goldColor= {255,215,0};
    string getgold= "$ ";
    getgold+=to_string(playergold);
    Textplayergold.loadFromRenderedText( getgold,goldColor);
    Textplayergold.rendermenu(5,5);


    BGframe.rendermenu(970,0);
    TroopsIcon1.render( &TextTroopsIcon1,1018,32,54,54,54);
    TroopsIcon2.render( &TextTroopsIcon2,1098,32,54,54,54);
    TroopsIcon3.render( &TextTroopsIcon3,1178,32,54,54,54);
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

int main(int argc,char** argv )
{
    Engine::GetInstance()->Init();
    TTF_Init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
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
                StartB.handleEvent(&e);
                if(StartC.handleEvent(&e)) quit = 1;
            }
            else if( trangthai == 1 )
            {
                if( NextA.handleEvent(&e) || NextB.handleEvent(&e) )
                {
                    if(NextB.handleEvent(&e)) chedokho=1;
                    trangthai = 2;
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
            while(!quit2)
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
                        if(Nwgbut.handleEvent(&e)) {trangthai=1;paused=0;quit2=1;}
                    }

                    dot.handleEvent(e);
                    if(TroopsIcon1.handleEvent(&e)) calling = 1;
                    if(TroopsIcon2.handleEvent(&e)) calling = 2;
                    if(TroopsIcon3.handleEvent(&e)) calling = 3;
                    if(e.type == SDL_KEYDOWN)
                    {
                        if(e.key.keysym.sym==SDLK_p)
                        {
                            paused=1;
                            SaveData();
                        }
                    }
                }
                if(!paused){
                    pre1();
                    AImove(chedokho, trangthai);

                    if(calling != 0)  CreateTroop(calling,0);
                    for(int i=0; i<danhsachquan.size(); i++)
                    {
                        if(danhsachquan[i].Textt.xx <-100 || danhsachquan[i].Textt.xx >3300) ClearTroop(danhsachquan[i].stt); //delete this one
                        if(danhsachquan[i].id < 7) Work(danhsachquan[i]);
                        else if(danhsachquan[i].id == 7) WorkHero(danhsachquan[i]);
                        else WorkBase(danhsachquan[i]);
                    }
                    frame++;
                    last1();
                }
                else Runpause();

                Engine::GetInstance()->Render();
            }
        }
//        if(trangthai==3) chuyen doi reset bien toan the vs danh sach
//        {
//            BG3.rendermenu(0,0);
//        }
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

    return 0;
}
