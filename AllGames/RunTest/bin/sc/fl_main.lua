#define	��ʼ��	oninit
#include "fl_base.lua"
shuangjieMJ = 1000;
quanjieMJ = 1000;
fl_main = nil;
function ������ʯ��ʾ()
	��ʼ������();
end
function oninit()
	setlanguage(readt("languages", "cn"));--��ʼ����������
	msgbox = dlg_search("msgbox");
	msgbox.display = false;
	fl_main = dlg_load("t_main");
	fl_main.pos = Pixel(0,0);
	fl_main:enable("background", true);
	fl_main:bind_click("�����", "����ð��ģʽ");
	fl_main:bind_click("������ս", "������սģʽ");
	fl_main:bind_click("������Ϸ", "���������Ϸ");
	fl_main:bind_click("������ʯ", "���빺��ҳ��");
	fl_main:bind_click("����", "��������");
	fl_main:bind_click("���а�", "�������а�");
	fl_main:bind_click("�������ʯ", "��������ʯ");
	fl_main:bind_click("����", "����Ϊ����");
	fl_main:bind_click("Ӣ��", "����ΪӢ��");
	fl_main:show("�������ʯ", false);
	if readi("gamefirst",0) == 0 then
		writei("magic", 100);--��ʼ����ֵ100
		writei("mojing", 0);
		writei("gamefirst",1);
		writei("ok_1", 1);
		local thistime = localtime();
		writei("fday", thistime.day);
		print("day:"..thistime.day);
	else
		--local thistime = math.abs(localtime().day-readi("fday", 0));
		--if thistime > 1 then
			--fl_main:show("�������ʯ", true);
		--end
		--print("day:"..localtime().day);
	end
	if insystem("android") then
		fl_main:show("�������ʯ", true);
	end
	��ʼ������();
end

function ����Ϊ����()
	
	������Ч("reset");
	writet("languages", "cn");
	goto("fl_main");
end
function ����ΪӢ��()
	������Ч("reset");
	writet("languages", "en");
	goto("fl_main");
end
function ��ʼ������()
	setvali("lianxu", 0);
	setvali("newrecord", 0);
	setvali("jifen", 0);
	local maxlx = readi("lianxu", 0);
	local maxstar = MAX_MISSIONS*3;
	local stars = 0;
	for i=0,(MAX_MISSIONS-1) do
		local s = readi("ok_"..i, 0);
		if s > 0 then
		stars = stars + (s-1);
		end
	end
	fl_main:setvalt("��ǰ�ؿ�ֵ", readi("current"));
	fl_main:setvalt("��ɶ�ֵ", int(stars/maxstar*100).."%");
	fl_main:setvali("�����������ֵ", maxlx);
	fl_main:setvali("��߻��ּ�¼ֵ", readi("newrecord", 0));
	local bwuxian = (readi("current")>20);
	fl_main:enable("����ģʽ", bwuxian);
	fl_main:show("���޿���", bwuxian==false);
	local besttime = readi("besttime", 0);
	local minute = int(besttime/60);
	local sec = int(besttime%60);
	if sec < 10 then
		sec = "0"..sec;
	end
	if minute < 10 then
		minute = "0"..minute;
	end
	fl_main:setvalt("���ʱ���", minute..":"..sec);
	setvali("reset", 1);
	local mojing = readi("mojing", 0);
	fl_main:setvali("��ǰ��ʯ", mojing);
end
function �ɹ�����()
end
function ���빺��ҳ��()
	������Ч("click");
	shop_buy("mjlink.buygem", "�ɹ�����");
end
function ����ð��ģʽ()
	������Ч("click");
	setvali("current", readi("current"));
	goto("fl_point");
end
function ������սģʽ()
	������Ч("click");
	setvali("beginsj", 10000);
	setvali("current", 10000);
	goto("fl_game");
end

function ���������Ϸ()
	������Ч("click");
	openurl("http:/\/www.aixspace.com/app");
end

function ��������()
	������Ч("click");
	gotocomment();
end

function �������а�()
	local maxstar = MAX_MISSIONS*3;
	local stars = 0;
	for i=0,(MAX_MISSIONS-1) do
		local s = readi("ok_"..i, 0);
		if s > 0 then
		stars = stars + (s-1);
		end
	end
	������Ч("click");
	achievement("mjlink.missioncomplete", int(stars/maxstar*100));
	rankscore("mjlink.maxscore", readi("newrecord", 0));
	rankscore("mjlink.maxmission", readi("lianxu", 0));
	openrank("");--��ʾ���а�
end

