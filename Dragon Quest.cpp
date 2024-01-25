#include <iostream>
#include <iomanip>
#include <cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
struct hero {
	int MAXHP, HP, DEF, MAXDEF, MP, MAXMP, ATK, LV, ChooseMoves, HaveMoves, poisoning, SunderArmor;
	string name, katana;
}hero;
struct monster {
	int MAXHP, HP, DEF, MAXDEF, MP, MAXMP, ATK, LV, ChooseMoves;
	string name;
}monster;
int rounds, battle, LackMP, die;
char JudgeString;
void skill()//技能介紹
{
	cout << "技能說明:" << endl;
	cout << "普通攻擊有10%機率雙倍傷害(爆擊)" << endl;
	cout << "破甲:破敵人DEF500（持續5回合）並向對方造成穿透傷害1000，消耗50MP" << endl;
	cout << "治癒術：我方回復2500生命值，消耗100MP" << endl;
	cout << "淬毒攻擊：向對方造成2500傷害，對方每回合受到1000中毒傷害，持續3回合，消耗100MP" << endl;
	if (battle == 1)
		cout << "最終一擊：向對方造成自身ATK*2的傷害，勇者生命變為1，消耗100MP" << endl;
	cout << endl;
}

void GradeUp()//升級
{
	int ChooseAttributes;
	while (true)
	{
		cout << "請選擇您要強化的體質（1）HP加1000（2）DEF加200（3）MP加250（4）ATK加1000：";
		cin >> JudgeString;
		ChooseAttributes = JudgeString - '0';
		if (JudgeString >= '0' && JudgeString <= '9')
		{
			if (ChooseAttributes == 1) {
				hero.MAXHP = hero.MAXHP + 1000;
				cout << "您的HP已上升1000" << endl;
				break;
			}
			else if (ChooseAttributes == 2) {
				hero.MAXDEF = hero.MAXDEF + 200;
				cout << "您的DEF已上升200" << endl;
				break;
			}
			else if (ChooseAttributes == 3) {
				hero.MAXMP = hero.MAXMP + 250;
				cout << "您的MP已上升250" << endl;
				break;
			}
			else if (ChooseAttributes == 4) {
				hero.ATK = hero.ATK + 1000;
				cout << "您的ATK已上升1000" << endl;
				break;
			}
			else {
				cout << "無此選擇" << endl;
				system("pause");
				system("cls");
			}
		}
		else cout << "輸入錯誤" << endl;
	}
}

void RoleValue()//角色數值
{
	system("pause");
	system("cls");
	die = 0, LackMP = 0;
	cout << "第" << rounds << "回合" << endl;
	cout << endl;
	cout << hero.name << ":HP=" << hero.HP << "/" << hero.MAXHP << " DEF=" << hero.DEF <<
	 " MP=" << hero.MP << " ATK=" << hero.ATK << " LV=" << hero.LV << endl;
	cout << monster.name << ":HP=" << monster.HP << "/" << monster.MAXHP << " DEF=" <<
	 monster.DEF << " MP=" << monster.MP << " ATK=" << monster.ATK << " LV=" << monster.LV << endl;
	cout << endl;
}

void UseSkill()//使用技能
{
	srand(time(NULL));
	int min = 1, max = 100;
	if (hero.ChooseMoves == 1) {
		int x = rand() % (max - min + 1) + min;
		if (x >= 10) {
			monster.HP = monster.HP + monster.DEF - hero.ATK;
			cout << hero.name << "使出了普通攻擊" << endl;
			cout << hero.name << "揮出了他的" << hero.katana << endl;
		}
		else {
			monster.HP = monster.HP + monster.DEF - hero.ATK * 2;
			cout << hero.name << "使出了普通攻擊" << endl;
			cout << hero.name << "揮出了他的" << hero.katana << "，不小心太用力了" << endl;
			cout << "恭喜爆擊" << endl;
		}
	}
	else if (hero.ChooseMoves == 2 && hero.MP >= 50) {
		monster.HP = monster.HP - 1000;
		monster.DEF = monster.DEF - 500;
		hero.MP = hero.MP - 50;
		hero.SunderArmor = 0;
		cout << hero.name << "使出了破甲" << endl;
		cout << hero.name << "用了他的" << hero.katana << "往對方的弱點打了下去" << endl;
	}
	else if (hero.ChooseMoves == 3 && hero.MP >= 100) {
		if (hero.HP + 2500 > hero.MAXHP)hero.HP = hero.MAXHP;
		else hero.HP = hero.HP + 2500;
		hero.MP = hero.MP - 100;
		cout << hero.name << "使出了治癒術" << endl;
		cout << hero.name << "手撫摸胸口，並且從地上冒出了綠色的圓圈" << endl;
		cout << hero.name << ":HP=" << hero.HP << "/" << hero.MAXHP << " DEF=" << hero.DEF <<
		 " MP=" << hero.MP << " ATK=" << hero.ATK << " LV=998" << endl;
	}
	else if (hero.ChooseMoves == 4 && hero.MP >= 100) {
		monster.HP = monster.HP + monster.DEF - 2500;
		hero.MP = hero.MP - 100;
		hero.poisoning = 0;
		cout << hero.name << "使出了淬毒攻擊" << endl;
		cout << hero.name << "從口袋掏出毒液塗到了" << hero.katana << "上並揮出" << endl;
	}
	else {
		cout << "你的MP不夠" << endl;
		system("pause");
		system("cls");
		LackMP = 1;
	}
}

void MonsterDebuff()//對面護甲值回復&中毒傷害 
{
	if (hero.SunderArmor < 5) {
		hero.SunderArmor = hero.SunderArmor + 1;
		if (hero.SunderArmor >= 5) {
			monster.DEF = monster.MAXDEF;
			cout << "對方護甲值回復" << endl;
		}
	}
	hero.poisoning = hero.poisoning + 1;
	if (hero.poisoning <= 4) {
		monster.HP = monster.HP - 1000;
		cout << "對方中毒受到了1000傷害" << endl;
	}
	if (monster.HP < 0)monster.HP = 0;
	cout << monster.name << ":HP=" << monster.HP << "/" << monster.MAXHP << " DEF=" << monster.DEF << " MP=----- ATK=" << monster.ATK << " LV=" << monster.LV << endl;
	rounds = rounds + 1;
	cout << endl;
}

void fighting()//戰鬥
{
	while (true) {
		RoleValue();
		if (battle == 0) { cout << "(0)技能介紹(1)普通攻擊(2)破甲(3)治癒術(4)淬毒攻擊:"; cin >> JudgeString; }
		else if (battle == 1) { cout << "(0)技能介紹(1)普通攻擊(2)破甲(3)治癒術(4)淬毒攻擊（5）最終一擊:"; cin >> JudgeString; }
		cout << endl;
		hero.ChooseMoves = JudgeString - '0';
		if (JudgeString >= '0' && JudgeString <= '9') {
			if (hero.ChooseMoves<0 || hero.ChooseMoves>hero.HaveMoves) {
				cout << "無招式" << endl;
				system("pause");
				system("cls");
				continue;
			}
			else if (hero.ChooseMoves == 0) {
				skill();
				continue;
			}
			if (battle == 1 && hero.ChooseMoves == 5 && hero.MP >= 100)
			{
				hero.HP = 1;
				hero.MP = hero.MP - 100;
				monster.HP = monster.HP + monster.DEF - hero.ATK * 2;
				cout << hero.name << "使出了最終一擊" << endl;
			}
			else {
				UseSkill();
				if (LackMP == 1)continue;
			}
			MonsterDebuff();
			if (0 >= monster.HP) {
				cout << "you win" << endl;
				system("pause");
				system("cls");
				cout<<(double)clock()/CLOCKS_PER_SEC<<endl;
				break;
			}
			hero.HP = hero.HP + hero.DEF - monster.ATK;
			if (hero.HP < 0)hero.HP = 0;
			cout << monster.name << "攻擊了" << hero.name << endl;
			cout << hero.name << ":HP=" << hero.HP << "/" << hero.MAXHP << " DEF=" << hero.DEF << " MP=" << hero.MP << " ATK=" << hero.ATK << " LV=" << hero.LV << endl;
			cout << endl;
			if (0 >= hero.HP) {
				cout << "you lose" << endl;
				system("pause");
				cout<<(double)clock()/CLOCKS_PER_SEC<<endl;
				die = 1;
				break;
			}
		}
		else {
			cout << "輸入錯誤" << endl;
			continue;
		}
	}
}

main()//戰鬥循環
{
	cout << "歡迎您冒險者，請輸入您的名字：";
	getline(cin, hero.name);
	cout << "歡迎您冒險者，請輸入您的劍的名字：";
	getline(cin, hero.katana);
	cout << "歡迎來到第一關" << endl;
	battle = 0, rounds = 1;
	hero = { 5000,5000,2000,2000,500,500,5000,998,1,4,5,6,hero.name,hero.katana };
	monster = { 10000,10000,1700,1700,0,0,4000,998,1,"蝙蝠" };
	fighting();
	if (die == 1)return 0;
	battle = 1, rounds = 1;
	cout << endl;
	cout << "恭喜您升到了" << hero.LV << "等，已恢復所有HP和MP，獲得新技能：最終一擊" << endl;
	GradeUp();
	hero = { hero.MAXHP,hero.MAXHP,hero.MAXDEF,hero.MAXDEF,hero.MAXMP,hero.MAXMP,hero.ATK,hero.LV + 1,0,hero.HaveMoves + 1,5,6,hero.name,hero.katana };
	monster = { 30000,30000,2000,2000,0,0,3500,999,0,"惡龍" };
	system("pause");
	system("cls");
	cout << "歡迎來到BOSS關" << endl;
	fighting();
	if (die == 1)return 0;
	system("pause");
	return 0;
}
