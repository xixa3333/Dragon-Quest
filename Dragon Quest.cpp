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
void skill()//�ޯश��
{
	cout << "�ޯ໡��:" << endl;
	cout << "���q������10%���v�����ˮ`(�z��)" << endl;
	cout << "�}��:�}�ĤHDEF500�]����5�^�X�^�æV���y����z�ˮ`1000�A����50MP" << endl;
	cout << "�v¡�N�G�ڤ�^�_2500�ͩR�ȡA����100MP" << endl;
	cout << "�f�r�����G�V���y��2500�ˮ`�A���C�^�X����1000���r�ˮ`�A����3�^�X�A����100MP" << endl;
	if (battle == 1)
		cout << "�̲פ@���G�V���y���ۨ�ATK*2���ˮ`�A�i�̥ͩR�ܬ�1�A����100MP" << endl;
	cout << endl;
}

void GradeUp()//�ɯ�
{
	int ChooseAttributes;
	while (true)
	{
		cout << "�п�ܱz�n�j�ƪ����]1�^HP�[1000�]2�^DEF�[200�]3�^MP�[250�]4�^ATK�[1000�G";
		cin >> JudgeString;
		ChooseAttributes = JudgeString - '0';
		if (JudgeString >= '0' && JudgeString <= '9')
		{
			if (ChooseAttributes == 1) {
				hero.MAXHP = hero.MAXHP + 1000;
				cout << "�z��HP�w�W��1000" << endl;
				break;
			}
			else if (ChooseAttributes == 2) {
				hero.MAXDEF = hero.MAXDEF + 200;
				cout << "�z��DEF�w�W��200" << endl;
				break;
			}
			else if (ChooseAttributes == 3) {
				hero.MAXMP = hero.MAXMP + 250;
				cout << "�z��MP�w�W��250" << endl;
				break;
			}
			else if (ChooseAttributes == 4) {
				hero.ATK = hero.ATK + 1000;
				cout << "�z��ATK�w�W��1000" << endl;
				break;
			}
			else {
				cout << "�L�����" << endl;
				system("pause");
				system("cls");
			}
		}
		else cout << "��J���~" << endl;
	}
}

void RoleValue()//����ƭ�
{
	system("pause");
	system("cls");
	die = 0, LackMP = 0;
	cout << "��" << rounds << "�^�X" << endl;
	cout << endl;
	cout << hero.name << ":HP=" << hero.HP << "/" << hero.MAXHP << " DEF=" << hero.DEF <<
	 " MP=" << hero.MP << " ATK=" << hero.ATK << " LV=" << hero.LV << endl;
	cout << monster.name << ":HP=" << monster.HP << "/" << monster.MAXHP << " DEF=" <<
	 monster.DEF << " MP=" << monster.MP << " ATK=" << monster.ATK << " LV=" << monster.LV << endl;
	cout << endl;
}

void UseSkill()//�ϥΧޯ�
{
	srand(time(NULL));
	int min = 1, max = 100;
	if (hero.ChooseMoves == 1) {
		int x = rand() % (max - min + 1) + min;
		if (x >= 10) {
			monster.HP = monster.HP + monster.DEF - hero.ATK;
			cout << hero.name << "�ϥX�F���q����" << endl;
			cout << hero.name << "���X�F�L��" << hero.katana << endl;
		}
		else {
			monster.HP = monster.HP + monster.DEF - hero.ATK * 2;
			cout << hero.name << "�ϥX�F���q����" << endl;
			cout << hero.name << "���X�F�L��" << hero.katana << "�A���p�ߤӥΤO�F" << endl;
			cout << "�����z��" << endl;
		}
	}
	else if (hero.ChooseMoves == 2 && hero.MP >= 50) {
		monster.HP = monster.HP - 1000;
		monster.DEF = monster.DEF - 500;
		hero.MP = hero.MP - 50;
		hero.SunderArmor = 0;
		cout << hero.name << "�ϥX�F�}��" << endl;
		cout << hero.name << "�ΤF�L��" << hero.katana << "����誺�z�I���F�U�h" << endl;
	}
	else if (hero.ChooseMoves == 3 && hero.MP >= 100) {
		if (hero.HP + 2500 > hero.MAXHP)hero.HP = hero.MAXHP;
		else hero.HP = hero.HP + 2500;
		hero.MP = hero.MP - 100;
		cout << hero.name << "�ϥX�F�v¡�N" << endl;
		cout << hero.name << "�⼾�N�ݤf�A�åB�q�a�W�_�X�F��⪺���" << endl;
		cout << hero.name << ":HP=" << hero.HP << "/" << hero.MAXHP << " DEF=" << hero.DEF <<
		 " MP=" << hero.MP << " ATK=" << hero.ATK << " LV=998" << endl;
	}
	else if (hero.ChooseMoves == 4 && hero.MP >= 100) {
		monster.HP = monster.HP + monster.DEF - 2500;
		hero.MP = hero.MP - 100;
		hero.poisoning = 0;
		cout << hero.name << "�ϥX�F�f�r����" << endl;
		cout << hero.name << "�q�f�U�ǥX�r�G���F" << hero.katana << "�W�ô��X" << endl;
	}
	else {
		cout << "�A��MP����" << endl;
		system("pause");
		system("cls");
		LackMP = 1;
	}
}

void MonsterDebuff()//�ﭱ�@�ҭȦ^�_&���r�ˮ` 
{
	if (hero.SunderArmor < 5) {
		hero.SunderArmor = hero.SunderArmor + 1;
		if (hero.SunderArmor >= 5) {
			monster.DEF = monster.MAXDEF;
			cout << "����@�ҭȦ^�_" << endl;
		}
	}
	hero.poisoning = hero.poisoning + 1;
	if (hero.poisoning <= 4) {
		monster.HP = monster.HP - 1000;
		cout << "��褤�r����F1000�ˮ`" << endl;
	}
	if (monster.HP < 0)monster.HP = 0;
	cout << monster.name << ":HP=" << monster.HP << "/" << monster.MAXHP << " DEF=" << monster.DEF << " MP=----- ATK=" << monster.ATK << " LV=" << monster.LV << endl;
	rounds = rounds + 1;
	cout << endl;
}

void fighting()//�԰�
{
	while (true) {
		RoleValue();
		if (battle == 0) { cout << "(0)�ޯश��(1)���q����(2)�}��(3)�v¡�N(4)�f�r����:"; cin >> JudgeString; }
		else if (battle == 1) { cout << "(0)�ޯश��(1)���q����(2)�}��(3)�v¡�N(4)�f�r�����]5�^�̲פ@��:"; cin >> JudgeString; }
		cout << endl;
		hero.ChooseMoves = JudgeString - '0';
		if (JudgeString >= '0' && JudgeString <= '9') {
			if (hero.ChooseMoves<0 || hero.ChooseMoves>hero.HaveMoves) {
				cout << "�L�ۦ�" << endl;
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
				cout << hero.name << "�ϥX�F�̲פ@��" << endl;
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
			cout << monster.name << "�����F" << hero.name << endl;
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
			cout << "��J���~" << endl;
			continue;
		}
	}
}

main()//�԰��`��
{
	cout << "�w��z�_�I�̡A�п�J�z���W�r�G";
	getline(cin, hero.name);
	cout << "�w��z�_�I�̡A�п�J�z���C���W�r�G";
	getline(cin, hero.katana);
	cout << "�w��Ө�Ĥ@��" << endl;
	battle = 0, rounds = 1;
	hero = { 5000,5000,2000,2000,500,500,5000,998,1,4,5,6,hero.name,hero.katana };
	monster = { 10000,10000,1700,1700,0,0,4000,998,1,"����" };
	fighting();
	if (die == 1)return 0;
	battle = 1, rounds = 1;
	cout << endl;
	cout << "���߱z�ɨ�F" << hero.LV << "���A�w��_�Ҧ�HP�MMP�A��o�s�ޯ�G�̲פ@��" << endl;
	GradeUp();
	hero = { hero.MAXHP,hero.MAXHP,hero.MAXDEF,hero.MAXDEF,hero.MAXMP,hero.MAXMP,hero.ATK,hero.LV + 1,0,hero.HaveMoves + 1,5,6,hero.name,hero.katana };
	monster = { 30000,30000,2000,2000,0,0,3500,999,0,"�c�s" };
	system("pause");
	system("cls");
	cout << "�w��Ө�BOSS��" << endl;
	fighting();
	if (die == 1)return 0;
	system("pause");
	return 0;
}
