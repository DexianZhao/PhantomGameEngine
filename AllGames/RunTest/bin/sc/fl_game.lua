#define	��ʼ��	oninit
#include "fl_base.lua"
fl_game = nil;
majiangs = {};
majiangs_sel = {};
majiangs_pos = {};
majiangs_exist = {};
majiangs_disable = {};
majiangs_count = 0;
majiangs_double = 41;
majiangs_zubie = 2;
fl_region = nil;
fl_effect = {};
fl_effect_play = {};
fl_effect_count = 6;
crystal_item = {};
crystal_scale = 0.5;
game_mj = {};
game_undos = {};
game_undo_count = 0;
game_mj_new = {};
game_mjcount_w = 6;
game_mjcount_h = 6;
mjwidth = 55;
mjheight = 70;
effect_mj_offset = 10;
game_time_enable = true;
game_begin = false;
game_mj_beginX = 0;
game_mj_beginY = 0;
game_mj_index = {};
game_mj_count = 0;
game_mj_exists = 0;
mojing_offset = 50;
mj_min_offset = 10;--�錢�����Ƅ�����
g_mousedisable = false;
mj_effects = {};
mj_effect_count = 0;
game_rect = nil;
��ʯ���ָ��� = 0;
�����û�״̬ = false;
g_movedisable = false;
chongzhi_guan = 16;
jiashi_guan = 24;
xiaochu_guan = 8;
help_array = {1,2,8,10,16,21,24,31};
help_array_name = {"xiaochu","tuitui","tishi","mofa", "chexiao","wuxuxiaochu","chuansong","zudang"};
xiaochu_eff = {};
xiaochu_pos = {};
xiaochu_pos_count = {};
xiaochu_index = 0;
function oninit()
	config = table_load("config.txt");
	fl_game = dlg_load("t_game");
	fl_game.pos = Pixel(0,0);
	fl_game:enable("background", true);
	--fl_game:bind_click("close", "�رղ��ܷ��عؿ�");
	fl_game:bind_click("pause", "��ͣ��Ϸ");
	--fl_game:bind_click("help", "��ʾ����");
	fl_region = fl_game:search("region");
	for i=0,(fl_effect_count-1) do
		fl_effect[i] = fl_game:search("effect"..(i+1));
	end
	xiaochu_eff[0] = fl_game:search("effect11");
	xiaochu_eff[1] = fl_game:search("effect12");
	xiaochu_eff[2] = fl_game:search("effect13");
	bind_input("down", "��ָ����");
	bind_input("up", "��ָ����");
	bind_input("move", "��ָ�ƶ�");
	bind_input("dbldown", "˫��ָ����");
	bind_input("dblup", "˫��ָ����");
	bind_input("dblmove", "˫��ָ�ƶ�");
	game_mjcount_w = config:id_i(getvali("current"), "������");
	game_mjcount_h = config:id_i(getvali("current"), "������");
	majiangs_zubie = config:id_i(getvali("current"), "���");
	mjcount_tbl = config:id_i(getvali("current"), "����");
	mjsize_tbl = config:id_i(getvali("current"), "�齫��С") * 55 / 100;
	ResetGame();
	g_savecombocount	=	0;
	--
	for i=0,(fl_effect_count-1) do
		crystal_item[i] = draw_create();
		crystal_item[i].context = 0;
		crystal_item[i].center = Pixel(128,128);
		fl_region:bind_draw(crystal_item[i]);
		crystal_item[i]:image("images/crystal.png");
		crystal_item[i].pos = Pixel(0, 0);
		crystal_item[i].scale = crystal_scale;
		crystal_item[i].clickscale = 1;
		crystal_item[i].display = false;
		crystal_item[i].layer = 101;
	end
end
move_crystal_dir = {};
move_crystal_begin = {};
function ������Чλ��(eff, mj)
	local pos = Pixel(game_mj_beginX+mj.x * mjwidth+45, game_mj_beginY+mj.y * mjheight+50);
	eff.display = true;
	pos.x = pos.x + fl_region.left;
	pos.y = pos.y + fl_region.top;
	eff.pos = pos;
	eff.effect_stop = true;
	eff.action = "Track";

end
function ��ʾ����()
	local current = getvali("current");
	local name = help_array_name[table.getn(help_array)];
	for x=1,(table.getn(help_array)-1) do
		print("TLL"..help_array[x]);
		if current < help_array[x+1] then
			name = help_array_name[x];
			break;
		end
	end
	��ʾ����ҳ��(name);
end
function �����ϳ��ӻ�()
	������Ч("click");
	timeout_1(500, "������һ������", "fl_shop");
end
function ��ʾ����ҳ��(name)
	-- cleartime("ʱ����ټ�ʱ");
	-- if fl_help == nil then
		-- fl_help = dlg_load("help");
	-- end
	-- cleartime("ʱ����ټ�ʱ");
	-- �����Ի���("help");
	-- fl_help.domodal = true;
	-- fl_help:bind_click("close", "�رհ���");
	-- fl_help:bind_click("image", "�رհ���");
	-- fl_help.display = true;
	-- fl_help:show("��ȡ����", false);
	-- fl_help:show("�ϳ��ӻ�", false);
	-- fl_help:bind_image("image", "help/"..name..".png");
end
function �رհ���()
	������Ϸ();
	if fl_help ~= nil then
		dlg_delete(fl_help);
		fl_help = nil;
	end
end
function ˢ�¹���ʹ��()
	local current = readi("current");
	if getvali("current") > current then
		current = getvali("current");
	end
	local xc =config:id_i(getvali("current"), "��ʱ��ʯ");
	local cz =config:id_i(getvali("current"), "������ʯ");
	local find =config:id_i(getvali("current"), "������ʯ");
	local mj = readi("mojing");
	fl_game:enable("��ʱ��ť", game_time_enable);--xc<=mj and game_time_enable);
	fl_game:enable("���ð�ť", true);--cz<=mj);
	fl_game:enable("������ť", true);--find<=mj);
	fl_game:enable("��ʱ˵��", game_time_enable);--xc<=mj and game_time_enable);
	fl_game:enable("����˵��", true);--cz<=mj);
	fl_game:enable("����˵��", true);--find<=mj);
	fl_game:enable("��ʱֵ", game_time_enable);--xc<=mj and game_time_enable);
	fl_game:enable("����ֵ", true);--cz<=mj);
	fl_game:enable("����ֵ", true);--find<=mj);

	fl_game:enable("����ť", true);
	fl_game:bind_click("��ʱ��ť", "����ʱ�书��");
	fl_game:bind_click("���ð�ť", "������Ϸ����");
	fl_game:bind_click("������ť", "�������һ��");
	fl_game:bind_click("����ť", "���빺��ҳ��");
	fl_game:show("��ʱ��ť", current >= jiashi_guan);
	fl_game:show("������ť", current >= xiaochu_guan);
	fl_game:show("���ð�ť", current >= chongzhi_guan);
	fl_game:show("��ʱ˵��", current >= jiashi_guan);
	fl_game:show("����˵��", current >= xiaochu_guan);
	fl_game:show("����˵��", current >= chongzhi_guan);
	fl_game:show("��ʱֵ", current >= jiashi_guan);
	fl_game:show("����ֵ", current >= xiaochu_guan);
	fl_game:show("����ֵ", current >= chongzhi_guan);
	fl_game:setvali("��ʱֵ", xc);
	fl_game:setvali("����ֵ", find);
	fl_game:setvali("����ֵ", cz);
end

fl_help = nil;

function ��ʼʱ��ʾ����()
	local current = getvali("current");
	local name = nil;
	for x=1,table.getn(help_array) do
		--print("TLL"..help_array[x]);
		if current == help_array[x] then
			name = help_array_name[x];
			break;
		end
	end
	if current >= 10000 and current < 11000 then
		name = "zhijiaoxiaochu";
		current = 10000;
	end
	if name == nil then
		return;
	end
	-- if readi("help"..current, 0) == 0 then
		-- writei("help"..current, 1);
	-- else
		-- return;
	-- end
	��ʾ����ҳ��(name);
end
function �������Ͽ�����(mjpos)
	local mjindex = game_mj[mjpos.x][mjpos.y];
	if majiangs_disable[mjindex] ~= 0 then
		return nil;
	end
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			local index = game_mj[x][y];
			if index >= 0 then
				if �Ƿ������(mjindex,index, false)==true then
					return Pixel(x,y);
				end
			end
		end
	end
	return nil;
end
function �滻һ���齫()
end

������λ��1 = nil;
������λ��2 = nil;
function �Ƿ�����������()
	������λ��1 = nil;
	������λ��2 = nil;
	local bok = false;
	local cnt = 0;
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			if game_mj[x][y] >= 0 then
				cnt = cnt+1;
			end
		end
	end
	if cnt == 0 then
		return true;
	end
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			if game_mj[x][y] >= 0 and majiangs_disable[game_mj[x][y]] == 0 then
				local ret = �������Ͽ�����(Pixel(x,y));
				if ret ~= nil then
					������λ��1 = Pixel(x,y);
					������λ��2 = ret;
					bok = true;
					break;
				end
			end
		end
		if bok then
			break;
		end
	end
	if ������λ��1 ~= nil then
		return true;
	end
	return false;
end
function ������Ϸ����()
	local mj = readi("mojing");
	if mj < config:id_i(getvali("current"), "������ʯ") then
		��ʯ����();
		������Ч("de");
		return;
	end
	fl_game:enable("���ð�ť", false);
	timeout(1000, "ˢ�¹���ʹ��");
	if �۳�ħ��(config:id_i(getvali("current"), "������ʯ"))==false then
		��ʯ����();
		������Ч("de");
		return;
	end
	������Ϸ���ص���Ϸ();
end

function ����ʱ�书��()
	local mj = readi("mojing");
	if mj < config:id_i(getvali("current"), "��ʱ��ʯ") then
		��ʯ����();
		������Ч("de");
		return;
	end
	fl_game:enable("��ʱ��ť", false);
	timeout(1000, "ˢ�¹���ʹ��");
	if �۳�ħ��(config:id_i(getvali("current"), "��ʱ��ʯ"))==false then
		��ʯ����();
		������Ч("de");
		return;
	end
	������Ч("addtime");
	game_time = game_time + 10;
	if game_time > game_time_length then
		game_time = game_time_length;
	end
	game_time_enable	=	false;
	timeout(10000, "ˢ��ʱ��ʹ��");
end
function ˢ��ʱ��ʹ��()
	game_time_enable = true;
	ˢ�¹���ʹ��();
end
function �������һ��()
	local mj = readi("mojing");
	if mj < config:id_i(getvali("current"), "������ʯ") then
		��ʯ����();
		������Ч("de");
		return;
	end
	fl_game:enable("������ť", false);
	timeout(1000, "ˢ�¹���ʹ��");
	if �Ƿ�����������() then
		if �۳�ħ��(config:id_i(getvali("current"), "������ʯ"))==false then
			��ʯ����();
			������Ч("de");
			return;
		end
		majiangs_sel[0].pos = Pixel(game_mj_beginX + ������λ��1.x * mjwidth, game_mj_beginY + ������λ��1.y * mjheight);
		majiangs_sel[1].pos = Pixel(game_mj_beginX + ������λ��2.x * mjwidth, game_mj_beginY + ������λ��2.y * mjheight);
		majiangs_sel[0].display = true;
		majiangs_sel[1].display = true;
	else
		������Ч("warning");
	end
	--��ӡgamemj();
end
function ���빺��ҳ��()
	������Ч("click");
	shop_buy("mjlink.buygem", "�ɹ�����");
end
function ������ʯ��ʾ()
	fl_game:setvali("��ǰ��ʯ", readi("mojing", 0));
end
function ��ʯ����()
	��ʾ��Ϸ������();
	local ��ʯ���� = fl_game_over:gsearch("��ʯ����");
	��ʯ����.display = true;
	��ʯ����:bind_click("����ť", "���빺��ҳ��");
	��ʯ����:show("�������ʯ", false);
	--��ʯ����:bind_click("�������ʯ", "��������ʯ");
	--local thistime = math.abs(localtime().day-readi("fday", 0));
	--if thistime > 1 then
		--��ʯ����:show("�������ʯ", true);
		--��ʯ����:bind_click("�������ʯ", "��������ʯ");
	--end
	if insystem("android") then
		��ʯ����:show("�������ʯ", true);
		��ʯ����:bind_click("�������ʯ", "��������ʯ");
	end
	��ʯ����:bind_click("����", "������Ϸ");
end
function ������Ϸ()
	��ʾ��Ϸ������(false);
	fl_game_over:show("����ʧ��", false);
	fl_game_over:show("������Ϸ", true);
	fl_game_over:bind_click("close", "�ر����ý���");
	fl_game_over:bind_click("����", "������Ϸ���ص���Ϸ");
	
end
function ���ؿؼ�(c)
	c.display = false;
end
function �۳�ħ��(n)
	local mj = readi("mojing");
	if mj < n then
		return false;
	end
	fl_game:setvalt("��ǰ��ʯ��", "-"..n)
	fl_game:show("��ǰ��ʯ��", true);
	fl_game:search("��ǰ��ʯ��").action = "aniout";
	fl_game:bind_event("onplayover", "��ǰ��ʯ��", "���ؿؼ�");
	writei("mojing", mj - n);
	fl_game:setvali("��ǰ��ʯ", readi("mojing", 0));
	return true;
end
function �ر����ý���()
	if fl_game_over ~= nil then
		ad_show(1, false);
		dlg_delete(fl_game_over);
		fl_game_over = nil;
	end
end
function ��Ϸ����()
	 if fl_game_over ~= nil then
		ad_show(1, false);
		 dlg_delete(fl_game_over);
		 fl_game_over = nil;
		 ������Ч("begin");
		game_mjcount_w = config:id_i(getvali("current"), "������");
		game_mjcount_h = config:id_i(getvali("current"), "������");
		majiangs_zubie = config:id_i(getvali("current"), "���");
		mjcount_tbl = config:id_i(getvali("current"), "����");
		mjsize_tbl = config:id_i(getvali("current"), "�齫��С") * 55 / 100;
		ResetGame();
	 end
end
function ������Ϸ���ص���Ϸ()
	������Ч("disable");
	local ary = {};
	local index = 0;
	for i=0,(game_mjcount_w-1) do
		for j=0,(game_mjcount_h-1) do
			local mjindex = game_mj[i][j];
			if mjindex >= 0 and majiangs_disable[mjindex] == 0 then
				ary[index] = {};
				ary[index][0] = i;
				ary[index][1] = j;
				ary[index][2] = mjindex;
				index = index + 1;
			end
		end
	end
	-- for i=0,(game_mjcount_w-1) do
		-- for j=0,(game_mjcount_h-1) do
			-- game_mj[i][j] = -1;
		-- end
	-- end
	random_table(index);
	for i=0,(index-1) do
		local idx = random_get(i);
		game_mj[ary[i][0]][ary[i][1]] = ary[idx][2];
	end
	for i=0,(fl_effect_count-1) do
		fl_effect_play[i] = 0;
	end
	index = 0;
	for i=0,(game_mjcount_w-1) do
		for j=0,(game_mjcount_h-1) do
			local mjindex = game_mj[i][j];
			if mjindex >= 0 then
				majiangs[mjindex].pos = Pixel(i*mjwidth+game_mj_beginX, j*mjheight+game_mj_beginY);
				timeout_1(index*50, "�齫���Գ���", mjindex);
				index = index + 1;
			end
		end
	end
	�����齫λ�����¼���GameMJ();
	 if fl_game_over ~= nil then
		 ad_show(1, false);
		 dlg_delete(fl_game_over);
		 fl_game_over = nil;
		 ������Ч("begin");
		-- ResetGame();
	 end
	if lastsel_mj~= nil then
		last_index = game_mj[lastsel_mj.x][lastsel_mj.y];
		majiangs[last_index].color = color4(1,1,1,1);
		lastsel_mj = nil;
	end
	timeout(1000, "ֹͣ���Ӳ���");
	timeout(1500, "�������Ӳ���");
end
mojing_index = 0;
move_last_begin = 0;
function ������ʯ(posin)
	local pos = Pixel(posin.x,posin.y);
	fl_game:setvali("��ǰ��ʯ", readi("mojing", 0));
	--cleartime("�ƶ���ʯ���·�");
	--cleartime("�����ŵ���ʯ��");
	mojing_index = mojing_index + 1;
	local sindex = mojing_index % fl_effect_count;
	writei("mojing", readi("mojing")+1);
	timeout(3000, "ˢ�¹���ʹ��");
	crystal_item[sindex].scale = crystal_scale;
	crystal_item[sindex].display = true;
	pos.x = pos.x - fl_region.left - mojing_offset - 70;
	pos.y = pos.y - fl_region.top - mojing_offset - 85;
	crystal_item[sindex].pos = pos;
	interval_1(50, "�����ŵ���ʯ��", sindex, 1000);
	move_crystal_begin[sindex] = crystal_item[sindex].pos;
	local mj = fl_game:search("����ť");
	move_crystal_dir[sindex] = Pixel(mj.left - fl_region.left - mojing_offset, mj.top - fl_region.top - mojing_offset - 20) - move_crystal_begin[sindex];
	--fl_effect[sindex].display = true;
	--fl_effect[sindex].effect_loop = 4;
	move_last_pos = Pixel(pos.x + 96 + fl_region.left,pos.y + 96 + fl_region.top);
	move_last_begin = 0;	
end
function �����ŵ���ʯ��(sindex, tm)
	local index = atoi(sindex);
	local s = math.sin(tm*12+1) + crystal_scale;
	if s < crystal_scale then
		s = crystal_scale;
	end
	crystal_item[index].scale = s;
	if tm > 0.35 then
		crystal_item[index].scale = crystal_scale;
		breaktime();
		interval_1(50, "�ƶ���ʯ���·�", sindex, 2000);
	end
end

function �ƶ���ʯ���·�(sindex, tm)
	local index = atoi(sindex);
	local newposx = move_crystal_begin[index].x + move_crystal_dir[index].x * tm;
	local newposy = move_crystal_begin[index].y + move_crystal_dir[index].y * tm;
	if move_last_begin == 0 then
		-- fl_effect[index].width = 64;
		-- fl_effect[index].height = 64;
		-- fl_effect[index].effect_stop = true;
		-- fl_effect[index].effect_loop = 5;
		-- fl_effect[index].action = "Track";
		-- move_last_begin = 1;
	end
	crystal_item[index].pos = Pixel(newposx, newposy);
	--fl_effect[index].moveleft = move_last_pos.x;
	--fl_effect[index].movetop = move_last_pos.y;
	move_last_pos = Pixel(newposx + 96 + fl_region.left,newposy + 96 + fl_region.top);
	if tm > 1 then
		breaktime();
		fl_effect[index].effect_stop = true;
		crystal_item[index].display = false;
		crystal_item[index].scale = 0.5;
		fl_game:setvali("��ǰ��ʯ", readi("mojing", 0));
		fl_game:setvalt("��ǰ��ʯ��", "+1")
		fl_game:show("��ǰ��ʯ��", true);
		fl_game:search("��ǰ��ʯ��").action = "ani";
		fl_game:bind_event("onplayover", "��ǰ��ʯ��", "���ؿؼ�");
	end
end


function ʱ����ټ�ʱ()
	game_time = game_time - 1;
	local star2 = config:id_i(getvali("current"), "2��ʱ��");
	if game_time < 0 then
		breaktime();
		g_mousedisable = true;
		local curr = getvali("current");
		if curr >= 10000 and curr < 11000 then
			timeout(500, "ˬ����ؽ���");
		else
			timeout(500, "��Ϸ����ʧ��");
		end
		setvali("reset", 1);
		������ʧ��Ч(fl_game:search("star3"));
		fl_game:enable("star1", false);
		fl_game:enable("star2", false);
		fl_game:enable("star3", false);
		return;
	elseif game_time < 10 and game_time < star2 then
		������Ч("lowtime");
	end
	����ʱ�����(game_time);
end
function ������ʧ��Ч(c)
	local stareff = fl_game:search("stareff");
	stareff.action = "ani";
	stareff.display = true;
	stareff.left = c.left;
	stareff.top = c.top;
	stareff.width=38;
	stareff.height = 38;
	stareff:bind_event("onplayover", "���ؿؼ�");
end
function ����ʱ�����(tm)
	-- local hour = int(tm/3600);
	-- local minute = int((tm%3600)/60);
	-- local second = int(tm%60);
	-- if second < 10 then
		-- second = "0"..second;
	-- end
	-- if minute < 10 then
		-- minute = "0"..minute;
	-- end
	-- if hour < 10 then
		-- hour = "0"..hour;
	-- end
	-- local endtime = localtime();
	-- local second = timediff_s(endtime, begin_time) - g_timeadd;
	-- tm = game_time_length - second;
	-- ppk_game:setvalt("ʱ��ֵ", hour..":"..minute..":"..second);
	local progress = tm / game_time_length;
	local ʱ�� = fl_game:search("ʱ��");
	ʱ��.right = 960*progress;
	local star1 = config:id_i(getvali("current"), "ʱ������");
	local star2 = config:id_i(getvali("current"), "2��ʱ��");
	local star3 = config:id_i(getvali("current"), "3��ʱ��");
	--local endtime = localtime();
	local second = game_time_length - tm;--timediff_s(endtime, begin_time) - g_timeadd;
	local text = "x3";
	if getvali("current") >= 10000 and getvali("current")<11000 then
		return;
	end
	fl_game:enable("star1", true);
	fl_game:enable("star2", true);
	fl_game:enable("star3", true);
	fl_game:show("star1", true);
	fl_game:show("star2", true);
	fl_game:show("star3", true);
	if tm>=star2 and tm < star3 then
		--print("gametime:"..game_time_length..","..tm..","..star3..","..second);
		if g_laststarcount ~= 3 then
			������ʧ��Ч(fl_game:search("star1"));
			g_laststarcount = 3;
			������Ч("lose");
		end
		fl_game:enable("star1", false);
	elseif tm < star2 then
		if g_laststarcount ~= 2 then
			������ʧ��Ч(fl_game:search("star2"));
			g_laststarcount = 2;
			������Ч("lose");
		end
		fl_game:enable("star1", false);
		fl_game:enable("star2", false);
	end
end
function �رղ��ܷ��عؿ�()
	������Ч("click");
	local oldi = getvali("current");
	if oldi >= 10000 then
		goto("fl_main");
	else
		goto("fl_point");
	end
end
begin_time = nil;
���ħ���������� = 0;
function ��ͣ��Ϸ()
	������Ч("click");
	��ʾ��Ϸ������();
	local ��ͣ��Ϸ = fl_game_over:gsearch("��ͣ��Ϸ");
	��ͣ��Ϸ.display = true;
	��ͣ��Ϸ:bind_click("�˳�", "�رղ��ܷ��عؿ�");
	��ͣ��Ϸ:bind_click("����", "������Ϸ");
	��ͣ��Ϸ:bind_click("����ť", "���빺��ҳ��");
	��ͣ��Ϸ:show("�������ʯ", false);
	--local thistime = math.abs(localtime().day-readi("fday", 0));
	--if thistime > 1 then
		--��ͣ��Ϸ:show("�������ʯ", true);
		--��ͣ��Ϸ:bind_click("�������ʯ", "��������ʯ");
	--end
	if insystem("android") then
		��ͣ��Ϸ:show("�������ʯ", true);
		��ͣ��Ϸ:bind_click("�������ʯ", "��������ʯ");
	end

	fl_game:show("region", false);
	fl_game:show("regionbg", false);
end
function ������Ϸ()
	������Ч("click");
	interval(1000,"ʱ����ټ�ʱ", game_time*2*1000);
	fl_game:show("region", true);
	fl_game:show("regionbg", true);
	if fl_game_over ~= nil then
		ad_show(1, false);
		dlg_delete(fl_game_over);
		fl_game_over = nil;
	end
end
g_combocount = 0;
g_combocountt = 0;
g_combocountg = 0;
g_combotime = 0;
g_laststarcount = 0;
function ResetGame()
	fl_game:show("������ʱ", false);
	g_combocount = 0;
	g_combocountt=0;
	last_index = -1;
	lastsel_mj = nil;
	g_combocountg=0;
	g_timeadd = 0;
	fl_game:show("region", true);
	fl_game:show("regionbg", true);
	fl_game:show("stareff", false);
	��������();
	g_combotime = apptime();
	g_movedisable = false;
	begin_time = localtime();
	game_undos = {};
	game_undo_count = 0;
	�����û�״̬ = false;
	mouse_down_mj = nil;
	fl_game:show("star1", true);
	fl_game:show("star2", true);
	fl_game:show("star3", true);
	g_lianji_c2 = fl_game:search("��������");
	g_lianji_c = fl_game:search("����ֵ");
	g_lianji_time = config:id_f(getvali("current"), "����ʱ��");
	g_lianji_c.display = false;
	g_lianji_c2.display = false;
	print("GAME_INDEX:"..getvali("current"));
	mjwidth = mjsize_tbl;
	mjheight = mjwidth/55*70;
	��ʯ���ָ��� = config:id_i(getvali("current"), "��ʯ���ָ���") / 100;
	���ħ���������� = config:id_i(getvali("current"), "�����ʯ��������");
	if getvali("reset")== 1 or (getvali("current") < 10000 or getvali("current") >= 11000) then
		game_time = config:id_i(getvali("current"), "ʱ������");
		game_time_length = game_time;
		setvali("reset", 0);
	end
	for i=0, (game_mj_count-1) do
		if game_mj_index[i] >= 0 then
			majiangs[game_mj_index[i]].display = false;
		end
	end
	����ʱ�����(game_time);
	interval(1000,"ʱ����ټ�ʱ", game_time*2*1000);
	mj_chanchu=0;
	if getvali("current") < 10000 then
		mj_chanchu = readi("mj_chanchu"..getvali("current"), 0);
	end
	fl_game:setvalt("��ʯֵ", mj_chanchu.."/"..���ħ����������);
	g_laststarcount = 4;
	local curI = getvali("current");
	fl_game:show("�ؿ�", false);
	fl_game:show("�����ؿ�", false);
	fl_game:show("�ؿ�ֵ", false);
	fl_game:show("�����ؿ�ֵ", false);
	fl_game:show("star1", curI<10000);
	fl_game:show("star2", curI<10000);
	fl_game:show("star3", curI<10000);
	fl_game:image_mode("star1", "ystar");
	fl_game:image_mode("star2", "ystar");
	fl_game:image_mode("star3", "ystar");
	fl_game:show("��û���", curI>=10000);
	fl_game:show("����ֵ", curI>=10000);
	fl_game:setvalt("����ֵ", "x"..getvali("jifen"));
	if curI >= 10000 and curI < 11000 then
		fl_game:show("�����ؿ�", true);
		fl_game:show("�����ؿ�ֵ", true);
		print("LIANXU:"..getvali("lianxu"));
		fl_game:setvali("�����ؿ�ֵ", getvali("lianxu") + 1);

	elseif curI<10000 then
		fl_game:show("�ؿ�", true);
		fl_game:show("�ؿ�ֵ", true);
		fl_game:setvali("�ؿ�ֵ", getvali("current"));
	else

	end
	--fl_game:setvali("����ֵ", readi("magic", 0));
	fl_game:setvali("��ǰ��ʯ", readi("mojing", 0));
	fl_game:show("��ǰ��ʯ��", false);
	local index = 0;
	majiangs_double = 0;
	for i=0,41 do
		majiangs_double = majiangs_double + 1;
		local name;
		if i <= 8 then
			name = "b_0"..(i+1);
		elseif i <= 17 then
			name = "t_0"..(i-8);
		elseif i <= 26 then
			name = "w_0"..(i-17);
		elseif i == 27 then
			name = "dong";
		elseif i == 28 then
			name = "xi";
		elseif i == 29 then
			name = "nan";
		elseif i == 30 then
			name = "bei";
		elseif i == 31 then
			name = "zhong";
		elseif i == 32 then
			name = "fa";
		elseif i == 33 then
			name = "bai";
		elseif i == 34 then
			name = "hua_chun";
		elseif i == 35 then
			name = "hua_xia";
		elseif i == 36 then
			name = "hua_qiu";
		elseif i == 37 then
			name = "hua_dong";
		elseif i == 38 then
			name = "hua_mei";
		elseif i == 39 then
			name = "hua_lan";
		elseif i == 40 then
			name = "hua_zhu";
		elseif i == 41 then
			name = "hua_ju";
		end
		for j=0,(majiangs_zubie-1) do
			if majiangs[index] == nil then
				majiangs[index] = draw_create();
				majiangs[index].context = index;
				majiangs[index].center = Pixel(22,25);
				fl_region:bind_draw(majiangs[index]);
			end
			majiangs[index]:image("images/mj.png");
			majiangs[index]:image_mode(name);
			majiangs[index]:set_rect(0,0,mjwidth/55*54,mjheight/70*78);
			majiangs[index].pos = Pixel((index%12)*70+j*24, 20 + int(index/12) * 26);
			majiangs[index].clickscale = 1.1;
			--majiangs[index]:bind_click("ѡ��һ���齫");
			index = index + 1;
		end
	end
	for i=0,1 do
		if majiangs_sel[i] == nil then
			majiangs_sel[i] = draw_create();
			majiangs_sel[i].context = i;
			majiangs_sel[i].center = Pixel(22,25);
			fl_region:bind_draw(majiangs_sel[i]);
			majiangs_sel[i]:image("images/mj.png");
			majiangs_sel[i]:image_mode("sel");
		end
		majiangs_sel[i]:set_rect(0,0,mjwidth/55*54,mjheight/70*78);
		majiangs_sel[i].pos = Pixel(0, 0);
		majiangs_sel[i].layer = 500;
		majiangs_sel[i].display = false;
	end
	majiangs_count = index;
	
	for i=0,(majiangs_count-1) do
		majiangs[i].display = false;
		majiangs_exist[i] = 0;
		majiangs_disable[i] = 0;
	end
	local count = int((game_mjcount_w*game_mjcount_h)/majiangs_zubie);
	random_table(majiangs_double);--count);--(game_mjcount_w*game_mjcount_w));
	local mjs = {};
	local indexcnt = 0;
	for i=0,(count-1) do
		for j=0,(majiangs_zubie-1) do
			mjs[indexcnt] = random_get(i)*majiangs_zubie+j;
			indexcnt=indexcnt+1;
		end
	end
	local cnt = (game_mjcount_w*game_mjcount_h)%majiangs_zubie;
	if cnt > 0 then
		for j=0,(cnt-1) do
			mjs[indexcnt] = random_get(count)*majiangs_zubie+j;
			indexcnt=indexcnt+1;
		end
	end
	local index = 0;
	local width = fl_region.width;
	local height = fl_region.height;
	game_mj_beginX = (width - (game_mjcount_w * mjwidth)) / 2;
	game_mj_beginY = (height - (game_mjcount_h * mjheight)) / 2;
	
	game_mj_index = {};
	game_mj_count = 0;
	local cnt = 0;
	local maxtime = 1000 / (game_mjcount_w*game_mjcount_h);
	if maxtime > 30 then
		maxtime = 30;
	end
	--game_mjcount_w = config:id_i(getvali("current"), "������");
	--game_mjcount_h = 
	local tbl = config:id_t(getvali("current"), "�ؿ���");
	local tempmj = {};
	local tempcnt = 0;
	local bExistMission = false;
	if tbl ~= "" then
		
		local mission = table_load("missions/"..tbl);
		bExistMission = true;
		for i=0,(game_mjcount_w-1) do
			tempmj[i] = {};
			for j=0,(game_mjcount_h-1) do
				tempmj[i][j] = mission:read_i(j,i);
				if tempmj[i][j] > 0 then
					tempcnt = tempcnt+1;
				end
			end
		end
		table_delete(mission);
	else
		tempcnt = mjcount_tbl;
	end
	random_table(tempcnt);--game_mjcount_w*game_mjcount_h);
	--fl_region.rect = Rect(0,0,gamewidth(),gameheight()-100);
	local mjsss = 0;
	local disableMj = 1;
	-- mjs[0] = majiangs_zubie*10;
	-- mjs[1] = majiangs_zubie*11;
	-- mjs[2] = majiangs_zubie*12;
	-- mjs[3] = majiangs_zubie*11+1;
	-- mjs[4] = majiangs_zubie*12+1;
	-- mjs[5] = majiangs_zubie*10+1;
	local mjlists = {};
	for k=0,(tempcnt-1) do
		mjlists[k] = random_get(k);
	end
	random_table(game_mjcount_w*game_mjcount_h);
	for i=0,(fl_effect_count-1) do
		fl_effect_play[i] = 0;
	end
	game_mj_exists = 0;
	for i=0,(game_mjcount_w-1) do
		game_mj[i] = {};
		for j=0,(game_mjcount_h-1) do
			game_mj[i][j] = -1;
		end
	end
	for imj=0,(tempcnt-1) do
			local indexs = random_get(imj);
			local x = (indexs%game_mjcount_w);
			local y = int(indexs/game_mjcount_w);
			local mjindex = mjs[mjlists[imj]];
			local mjsfind = false;
			while true do
				local tempmj2 = disableMj;
				for k=0,(tempcnt-1) do
					if int(mjs[k]/majiangs_zubie) == int(disableMj/majiangs_zubie) then
						disableMj = disableMj+majiangs_zubie;
						break;
					end
				end
				if tempmj2 == disableMj then
					break;
				end
			end
			--print("mjindex:"..mjsss..","..random_get(mjsss)..","..mjindex..","..disableMj);
			if bExistMission==false or tempmj[x][y]~=0 then
				if tbl ~= "" and tempmj[x][y]<0 then
					mjindex = disableMj;--mjs[tempcnt];
					disableMj=disableMj+1;
					if tempmj[x][y] < 0 then
						majiangs[mjindex]:image_mode("�����ƶ�");
						majiangs[mjindex]:set_rect(0,0,mjwidth/55*54,mjheight/70*78);
						majiangs_disable[mjindex] = 1;
					--else
						--majiangs_disable[mjindex] = -1;
						--majiangs[mjindex]:image_mode("space");
					end
					
				else
					majiangs_disable[mjindex] = 0;
					game_mj_exists = game_mj_exists+1;
				end
				game_mj[x][y] = mjindex;
				majiangs_exist[mjindex] = 1;
				game_mj_index[game_mj_count] = mjindex;
				majiangs[mjindex].context = x*1000 + y;
				majiangs[mjindex].display = false;
				
				majiangs[mjindex].layer = x + y * game_mjcount_w;
				majiangs[mjindex].pos = Pixel(game_mj_beginX + x * mjwidth, game_mj_beginY + y * mjheight);
				majiangs_pos[mjindex] = Pixel(game_mj_beginX + x * mjwidth, game_mj_beginY + y * mjheight);
				majiangs[mjindex].color = color4(1,1,1,1);
				if bExistMission==false or (tbl ~= "" and tempmj[x][y]>0) then
					mjsss = mjsss + 1;
				else
					--mjsss = mjsss + 1;
				end
				game_mj_count = game_mj_count+1;
				
				timeout_1(cnt*maxtime, "�齫���Գ���", mjindex);
				cnt = cnt + 1;
			else
			game_mj[x][y] = -1;--mjindex;
			end
	end
	game_rect = Rect(game_mj_beginX, game_mj_beginY, game_mj_beginX+game_mjcount_w * mjwidth,game_mj_beginY+game_mjcount_h * mjheight);
	UpdateRegionBG();
	--game_rect.top = 0;
	������Ч("begin");
	fl_region:sort_draws();--����ȾĿ����в������
	game_begin = true;
	g_mousedisable = false;
	timeout(1000, "ֹͣ���Ӳ���");
	timeout(1500, "�������Ӳ���");
	game_time_enable = true;
	ˢ�¹���ʹ��();
	cleartime("ˢ��ʱ��ʹ��");
	--��ʼʱ��ʾ����();
	--��ӡgamemj();
	fl_game:setvalt("ʣ��ֵ", game_mj_exists.."/"..game_mj_exists);
end
function ��ӡgamemj()
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			print("gamemj["..x.."]["..y.."]="..game_mj[x][y]);
		end
	end
	for i=0,(game_mj_count-1) do
		local mj = game_mj_index[i];
		local d = 1;
		if majiangs[mj].display==false then
		d=0;
		end
		print("majiang:"..mj..":display="..d..","..majiangs[mj].pos.x..","..majiangs[mj].pos.y);
	end
end
function UpdateRegionBG()
	local grect = Rect(game_mj_beginX, game_mj_beginY, game_mj_beginX+game_mjcount_w * mjwidth,game_mj_beginY+game_mjcount_h * mjheight);
	local regionbg = fl_game:search("regionbg");
	local x = fl_region.left;
	local y = fl_region.top;
	regionbg.rect = Rect(grect.left + x-2, grect.top+y-2, grect.right+x+2, grect.bottom+y+(mjheight/6));
end
--function ���·���ֵ()

--end
b˫��ָ���� = false;
˫��ָ���µ� = nil;
function ˫��ָ����(pt1,pt2)
	b˫��ָ���� = true;
	˫��ָ���µ� = pt1;
	local mj = �����µ��齫(pt2);
	if mj ~= nil then
		if �Ƿ���������齫(mouse_down, mj) then
			���������齫(mouse_down, mj, true);
			mouse_down = nil;
			mouse_down_mj = nil;
			b˫��ָ���� = false;
		end
	end
end

function ˫��ָ�ƶ�(pt)
	if game_rect==nil or game_begin == false then
		return;
	end
	if b˫��ָ���� ==false then
		return;
	end
	local off = pt - ˫��ָ���µ�;
	local left = fl_region.left - game_rect.left;
	if left < 0 then
		left = left + off.x;
		if left > 0 then
			left = 0;
		end
	end
	--fl_region.left = left + game_rect.left;
	game_mj_beginX = game_mj_beginX + off.x;
	game_mj_beginY = game_mj_beginY + off.y;
	local width = mjwidth*(game_mjcount_w) - fl_region.width;
	local height = mjheight*(game_mjcount_h) - fl_region.height;
	if game_rect.left < 0 then
		if game_mj_beginX > 0 then
			game_mj_beginX = 0;
		end
		if game_mj_beginX < -width then
			game_mj_beginX = -width;
		end
	else
		game_mj_beginX = game_rect.left;
	end
	if game_rect.top < 0 then
		if game_mj_beginY > 0 then
			game_mj_beginY = 0;
		end
		if game_mj_beginY < -height then
			game_mj_beginY = -height;
		end
	else
		game_mj_beginY = game_rect.top;
	end
	if game_mj_beginX ~= game_rect.left or game_mj_beginY ~= game_rect.top then
		for i=0,(game_mjcount_w-1) do
			for j=0,(game_mjcount_h-1) do
				local mjindex = game_mj[i][j];
				if mjindex >= 0 then
					majiangs[mjindex].pos = Pixel(game_mj_beginX + i * mjwidth, game_mj_beginY + j * mjheight);
					majiangs_pos[mjindex] = Pixel(game_mj_beginX + i * mjwidth, game_mj_beginY + j * mjheight);
				end
			end
		end
	end
	UpdateRegionBG();
	˫��ָ���µ� = pt;
end

function ˫��ָ����(pt)
	b˫��ָ���� = false;
end
function ֹͣ���Ӳ���()
	for i=0,(fl_effect_count-1) do
		fl_effect[i].effect_stop = true;
	end
end
function �������Ӳ���()
	for i=0,(fl_effect_count-1) do
		fl_effect[i].display = false;
	end
end
function �齫�������Գ���(idx, tm)
	local index = atoi(idx);
	tm = tm*5;
	majiangs[index].opacity = tm;
	if tm > 1 then
		breaktime();
		majiangs[index].opacity = 1;
	end
end

function �齫���Գ���(idx)
	local index = atoi(idx);
	local pos1 = Pixel(majiangs_pos[index].x, majiangs_pos[index].y);
	local sindex = index % fl_effect_count;
	fl_effect[sindex].moveleft = pos1.x+mjwidth/4;
	fl_effect[sindex].movetop = pos1.y+mjheight/2;
	fl_effect[sindex].width = mjwidth;
	fl_effect[sindex].height = mjheight;
	--if fl_effect_play[sindex] == 0 then
		fl_effect_play[sindex] = 1;
		fl_effect[sindex].action = "Track";
		fl_effect[sindex].display = true;
		fl_effect[sindex].effect_loop = 1;
	--end
	majiangs[index].display = true;
	majiangs[index].opacity = 0;
	interval_1(50, "�齫�������Գ���", idx, 200);
end
lastsel_mj = nil;
function getmin(v1,v2)
	if v1>v2 then
		return v2;
	end
	return v1;
end
function getmax(v1,v2)
	if v1>v2 then
		return v1;
	end
	return v2;
end
function �����齫λ��ȡ������(pos)
	local ret =  Pixel(int((pos.x - game_mj_beginX + mjwidth/2) / mjwidth),int((pos.y - game_mj_beginY+mjheight/2)/mjheight));
	if ret.x < 0 then
		ret.x = 0;
	elseif ret.x >= game_mjcount_w then
		ret.x = game_mjcount_w-1;
	end
	if ret.y < 0 then
		ret.y = 0;
	elseif ret.y >= game_mjcount_h then
		ret.y = game_mjcount_h-1;
	end
	return ret;
end
function ����������Ч(idx, tm)
	tm = tm * 5.0;
	local index = atoi(idx);
	-- local id = int(tm/0.2);
	-- local xx = int(id/2);
	-- local yy = int(id%2);
	-- if xx > 1 then
		-- xx = 1;
	-- end
	mj_effects[index]:image_rect(0,0,256,256);
	mj_effects[index].scale = 2-tm*2;--math.sin(tm*5+1)*2;
	mj_effects[index].opacity = 1-tm*0.8;--math.sin(tm*5);
	--majiangs[mj_effects[index].context].opacity = (2-tm);
	if tm > 1 then--id >= 4 then
		breaktime();
		mj_effects[index].display = false;
		majiangs[mj_effects[index].context].display = false;
	end
end
function ����������Ч�ȴ�(tm)
	interval_1(50, "����������Ч", tm, 10000);
end
function ��������Ч��(pos, mjindex, wait)
	local index = mj_effect_count;
	for i=0,(mj_effect_count-1) do
		if mj_effects[i].display == false then
			index = i;
			break;
		end
	end
	if mj_effects[index] == nil then
		mj_effects[index] = draw_create();
		mj_effects[index]:image("images/slace.png");
		mj_effects[index]:image_rect(0, 0, 256, 256);
		mj_effects[index].center = Pixel(64,64);
		mj_effects[index]:set_rect(0, 0, 128, 128);
		mj_effects[index].clickscale = 1;
		mj_effects[index].layer = 100;
		fl_region:bind_draw(mj_effects[index]);
	end
	if index == mj_effect_count then
		mj_effect_count = mj_effect_count+1;
	end
	mj_effects[index].display = true;
	mj_effects[index].opacity = 0;
	mj_effects[index].context = mjindex;
	mj_effects[index].pos = Pixel(game_mj_beginX+pos.x * mjwidth-mjwidth/4, game_mj_beginY+pos.y * mjheight);
	interval_1(50, "����������Ч", index, 10000);
	--timeout_1(wait, "����������Ч�ȴ�", index);
end
effect_c = nil;
effect_pos = {};
effect_pos_count = 0;
effect_speed = 10;

function ����·���������Ӽ���(sindex, tm)
	local index = atoi(sindex);
	local count = xiaochu_pos_count[index];
	tm = tm*effect_speed;
	local findex = int(tm);
	local findex2 = findex+1;
	if findex2 >= count then
		effect_c.pos = xiaochu_pos[index][count-1] + Pixel(mjwidth/4,0);
		effect_c.effect_stop = true;
		breaktime();
	else
		local ltm = tm - findex;
		local dir = xiaochu_pos[index][findex2] - xiaochu_pos[index][findex];
		if ltm > 1 then
			ltm = 1;
		end
		effect_c.pos = Pixel(xiaochu_pos[index][findex].x+dir.x*ltm, xiaochu_pos[index][findex].y+dir.y*ltm);
	end
end
function ����·���������ӵȴ�(sindex)
	local index = atoi(sindex);
	effect_c.display = true;
	effect_c.pos = xiaochu_pos[index][0];
	effect_c.action = "Track";
	interval_1(50, "����·���������Ӽ���", sindex, 10000);
end
function ����·����������(eff, speed)
	effect_c	=	eff;
	effect_c.width = mjwidth/4;
	effect_c.height = mjheight/4;
	effect_speed = speed;
	local xc = xiaochu_index%3;
	xiaochu_pos[xc] = {};
	for i=0,(effect_pos_count-1) do
		xiaochu_pos[xc][i] = effect_pos[i] + Pixel(mjwidth/1.2,mjheight/4);
	end
	xiaochu_pos_count[xc] = effect_pos_count;
	timeout_1(200, "����·���������ӵȴ�", xc);
end
g_zhijiao_pos = nil;
g_zhijiao_pos2 = nil;
function �Ƿ����赲X(xfrom, xto, y, exc1,exc2)
    if y<0 or y>=game_mjcount_h then
        return false;
    end
    local x1 = getmin(xfrom, xto);
    local x2 = getmax(xfrom, xto);
    for x=x1,x2 do
        if x<0 or x>=game_mjcount_w then
        elseif game_mj[x][y]>=0 then
			if game_mj[x][y]==exc1 or game_mj[x][y]==exc2 then
			elseif majiangs_disable[game_mj[x][y]]~=0 then
				return true;
			else
				return true;
			end
        end
    end
    return false;
end
function �Ƿ����赲Y(yfrom, yto, x, exc1,exc2)
    if x<0 or x>=game_mjcount_w then
        return false;
    end
    local y1 = getmin(yfrom, yto);
    local y2 = getmax(yfrom, yto);
    for y=y1,y2 do
        if y<0 or y>=game_mjcount_h then
        elseif game_mj[x][y]>=0 then
			if game_mj[x][y]==exc1 or game_mj[x][y]==exc2 then
			elseif majiangs_disable[game_mj[x][y]]~=0 then
				return true;
			else
				return true;
			end
        end
    end
    return false;
end
function �����������(x,y)
	effect_pos[effect_pos_count] = Pixel(x,y);
	effect_pos_count = effect_pos_count+1;
	if effect_pos_count > 1 then
		effect_pos[effect_pos_count] = Pixel(x,y);
		effect_pos_count = effect_pos_count+1;
	end
end
function ����ID����Pos(index)
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			if game_mj[x][y] == index then
				return Pixel(x,y);
			end
		end
	end
	return nil;
end
function �Ƿ������(index1, index2, addpoint)
	if index1 == index2 then
		return false;
	end
	if majiangs_disable[index1] ~= 0 or majiangs_disable[index2] ~= 0 then
		return false;
	end
	if int(index1/majiangs_zubie) ~= int(index2/majiangs_zubie) then--���������ͬһ���齫
		return false;
	end
	if index1 < 0 or index2 < 0 then
		return false;
	end
	local mj1 = majiangs[index1];
	local mj2 = majiangs[index2];
	local m1x = -1;
	local m1y = -1;
	local m2x = -1;
	local m2y = -1;
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			if game_mj[x][y] == index1 then
				m1x = x;
				m1y = y;
				break;
			end
		end
	end
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			if game_mj[x][y] == index2 then
				m2x = x;
				m2y = y;
				break;
			end
		end
	end
	--print("pos:m1x="..m1x..",m2x="..m2x..",m1y="..m1y..",m2y="..m2y..","..index1..","..index2);
	if m1x<0 or m2x <0 then
		return false;
	end
	local dx = m2x - m1x;
	local dy = m2y - m1y;
	local ldx = abs(dx);
	local ldy = abs(dy);
	if addpoint then
		effect_pos_count = 0;
		�����������(m1x,m1y);
	end
	if m1x==m2x then
		if �Ƿ����赲Y(m1y, m2y, m1x, index1, index2)==false then
			if addpoint then
				�����������(m2x,m2y);
			end
			return true;
		end
	elseif m1y==m2y then
		if �Ƿ����赲X(m1x, m2x, m1y, index1, index2)==false then
			if addpoint then
				�����������(m2x,m2y);
			end
			return true;
		end
	elseif �Ƿ����赲X(m1x, m2x, m1y, index1, index2) ==false and �Ƿ����赲Y(m1y, m2y, m2x, index1, index2) ==false then
		if addpoint then
			�����������(m2x,m1y);
			�����������(m2x,m2y);
		end
		return true;
	elseif �Ƿ����赲X(m1x, m2x, m2y, index1, index2) ==false and �Ƿ����赲Y(m1y, m2y, m1x, index1, index2) ==false then
		if addpoint then
			�����������(m1x,m2y);
			�����������(m2x,m2y);
		end
		return true;
	end
	for x=0,(m1x+1) do
        if �Ƿ����赲X(m1x, m1x-x, m1y, index1, index2) then
            break;
        end
        if �Ƿ����赲Y(m1y, m2y, m1x-x, index1, index2) == false and �Ƿ����赲X(m1x-x, m2x, m2y, index1, index2) == false then
			--print("lian ok1"..(m1x-x)..","..m1y..","..m2y);
			if addpoint then
				if x>0 then
					�����������(m1x-x,m1y);
					�����������(m1x-x,m2y);
				else
					�����������(m1x,m2y);
				end
				�����������(m2x,m2y);
			end
			return true;
        end
	end
	for x=m1x,game_mjcount_w do
        if �Ƿ����赲X(m1x, x, m1y, index1, index2) then
            break;
        end
        if �Ƿ����赲Y(m1y, m2y, x, index1, index2) == false and �Ƿ����赲X(x, m2x, m2y, index1, index2) == false then
			--print("lian ok2"..x..","..m1y..","..m2y);
			if addpoint then
				if x>m1x then
					�����������(x,m1y);
					�����������(x,m2y);
				else
					�����������(m1x,m2y);
				end
				�����������(m2x,m2y);
			end
			return true;
        end
	end
	for y=0,(m1y+1) do
        if �Ƿ����赲Y(m1y, m1y-y, m1x, index1, index2) then
            break;
        end
        if �Ƿ����赲X(m1x, m2x, m1y-y, index1, index2) == false and �Ƿ����赲Y(m1y-y, m2y, m2x, index1, index2) == false then
			--print("lian ok3"..(m1y-y)..","..m1x..","..m2x);
			if addpoint then
				if y>0 then
					�����������(m1x,m1y-y);
					�����������(m2x,m1y-y);
				else
					�����������(m2x,m1y);
				end
				�����������(m2x,m2y);
			end
			return true;
        end
	end
	for y=m1y,(game_mjcount_h+1) do
        if �Ƿ����赲Y(m1y, y, m1x, index1, index2) then
            break;
        end
        if �Ƿ����赲X(m1x, m2x, y, index1, index2) == false and �Ƿ����赲Y(y, m2y, m2x, index1, index2) == false then
			--print("lian ok4"..y..","..m1x..","..m2x);
			if addpoint then
				if y>m1y then
					�����������(m1x,y);
					�����������(m2x,y);
				else
					�����������(m2x,m1y);
				end
				�����������(m2x,m2y);
			end
			return true;
        end
	end
	return false;
end
function �Ƿ���������齫(mj1, mj2)
	local index1 = game_mj[mj1.x][mj1.y];
	local index2 = game_mj[mj2.x][mj2.y];
	if index1==index2 then
		return false;
	end
	if majiangs_disable[index1] ~= 0 or majiangs_disable[index2] ~= 0 then
		return false;
	end
	if int(index1/majiangs_zubie) == int(index2/majiangs_zubie) then--���������ͬһ���齫
		if index1 >= 0 and index2 >= 0 and �Ƿ������(index1, index2) then
			return true;
		end
	end
	return false;
end
�û��齫1 = nil;
�û��齫2 = nil;
�û��齫λ��1 = nil;
�û��齫λ��2 = nil;
function �����齫λ���û�(tm)
	tm = tm * 2;
	local pos = �û��齫λ��2 - �û��齫λ��1;
	local pos1 = Pixel(pos.x*tm+�û��齫λ��1.x, pos.y*tm+�û��齫λ��1.y);
	local pos2 = Pixel(pos.x*(1-tm)+�û��齫λ��1.x, pos.y*(1-tm)+�û��齫λ��1.y);
	majiangs[�û��齫1].pos = pos1;
	majiangs[�û��齫2].pos = pos2;
	pos1.y = pos1.y + 60;
	pos2.y = pos2.y + 60;
	fl_effect[0].pos = pos1;
	fl_effect[1].pos = pos2;
	if tm >= 1 then
		breaktime();
		g_mousedisable = false;
		�����齫λ�����¼���GameMJ();
	end
end
function Undo()
	if game_undo_count <= 0 then
		return;
	end
	game_undo_count = game_undo_count - 1;
	for i=0,(game_mj_count-1) do
		local mj = game_mj_index[i];
		majiangs[mj].display = false;
		majiangs_exist[mj] = 0;
	end
	--print("UNDO"..game_undo_count);
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			game_mj[x][y] = 	game_undos[game_undo_count][x][y];
			local mjindex = game_mj[x][y];
			if mjindex >= 0 then
				majiangs_exist[mjindex] = 1;
				majiangs_pos[mjindex] = Pixel(x*mjwidth+game_mj_beginX, y*mjheight+game_mj_beginY);
				majiangs[mjindex].pos = majiangs_pos[mjindex];
				majiangs[mjindex].display = true;
				majiangs[mjindex].color = color4(1,1,1,1);
				majiangs[mjindex].layer = x+y*game_mjcount_w;
			end
		end
	end
	fl_region:sort_draws();
	game_undos[game_undo_count] = nil;
end
function ���������齫(mj1,mj2, ������Ϸ����)
	--game_undos = {};
	game_undos[game_undo_count] = {};
	for i=0,(game_mjcount_w-1) do
		game_undos[game_undo_count][i] = {};
		for j=0,(game_mjcount_h-1) do
			game_undos[game_undo_count][i][j] = game_mj[i][j];
		end
	end
	game_undo_count = game_undo_count + 1;
	--print("ADDUNDO"..game_undo_count);
	local index1 = game_mj[mj1.x][mj1.y];
	local index2 = game_mj[mj2.x][mj2.y];
	if �����û�״̬ then
		g_mousedisable = true;
		majiangs_sel[0].display = false;
		if lastsel_mj~= nil then
			last_index = game_mj[lastsel_mj.x][lastsel_mj.y];
			majiangs[last_index].color = color4(1,1,1,1);
			lastsel_mj = nil;
		end
		�û��齫1 = index1;
		�û��齫2 = index2;
		�û��齫λ��1 = majiangs[index1].pos;
		�û��齫λ��2 = majiangs[index2].pos;
		majiangs[index1].layer = 100;
		majiangs[index2].layer = 100;
		fl_region:sort_draws();
		game_mj[mj1.x][mj1.y] = index2;
		game_mj[mj2.x][mj2.y] = index1;
		������Чλ��(fl_effect[0], mj1);
		������Чλ��(fl_effect[1], mj2);
		fl_game:enable("��ʱ��ť",true);
		������Ч("de");
		�����û�״̬ = false;
		interval(50, "�����齫λ���û�", 2000);
		return true;
	end


	local ret = false;
	if index1 >= 0 and index2 >= 0 and index1 ~= index2 and int(index1/majiangs_zubie) == int(index2/majiangs_zubie) then--���������ͬһ���齫
		if �Ƿ������(index1, index2, true)==true then
			ret = true;
			local b1 = 0;
			if majiangs[index1].display then
				b1 = 1;
			end
			local b2 = 0;
			if majiangs[index2].display then
				b2 = 1;
			end
			majiangs_exist[index1] = 0;
			majiangs_exist[index2] = 0;
			��������Ч��(mj1, index1, 0);
			��������Ч��(mj2, index2, 0);
			for i1=0,(effect_pos_count-1) do
				effect_pos[i1] = Pixel(game_mj_beginX+effect_pos[i1].x * mjwidth+45, game_mj_beginY+effect_pos[i1].y * mjheight+fl_region.top+50);
			end
			����·����������(xiaochu_eff[(xiaochu_index+1)%3], 15);
			local current = getvali("current");
			if current < 10000 then
				mj_chanchu = readi("mj_chanchu"..current, 0);--ħ������������-��������*(ħ������������*0.5);
			end
			--���ֵ�Խ�����Խ�ѵõ�,combo����Խ�ߣ�ħ�����ָ��ʸ���
			local gailv_l = (g_combocount-1)/2 * (��ʯ���ָ���*0.5);
			if gailv_l > ��ʯ���ָ��� then
				gailv_l = ��ʯ���ָ���;
			elseif gailv_l < 0 then
				gailv_l = 0;
			end
			local gailv = (��ʯ���ָ��� - (mj_chanchu/���ħ����������)*(��ʯ���ָ���*0.5)) + gailv_l;--g_combocount/5
			local bMJchuxian = false;
			if math.random() < gailv then
				if mj_chanchu >= ���ħ���������� then
				else
					bMJchuxian = true;
					������ʯ(effect_pos[0]);
					mj_chanchu = mj_chanchu + 1;
					if current < 10000 then
						writei("mj_chanchu"..current, mj_chanchu);
					end
					fl_game:setvalt("��ʯֵ", mj_chanchu.."/"..���ħ����������);
				end
			end
			g_movedisable = false;
			if ��������() == false then
				if bMJchuxian then
					������Ч("gomojing");
				else
					������Ч("xiaochu");
				end
			end
			local mjc = 0;
			for x=0,(game_mjcount_w-1) do
				for y=0,(game_mjcount_h-1) do
					if game_mj[x][y]>=0 and majiangs_disable[game_mj[x][y]]==0 then
						mjc = mjc+1;
					end
				end
			end
			fl_game:setvalt("ʣ��ֵ", (mjc-2).."/"..game_mj_exists);
			ˢ�¹���ʹ��();
		end
	end
	if lastsel_mj~= nil then
		last_index = game_mj[lastsel_mj.x][lastsel_mj.y];
		majiangs[last_index].color = color4(1,1,1,1);
		lastsel_mj = nil;
	end
	if ������Ϸ���� then
		if �����齫λ�����¼���GameMJ() == false then
			if �Ƿ�����������() == false then
				timeout(100, "�޿�������");
			end
		end
	end

	return ret;
end

function ��������()
end
function �����ı�͸��(name, c)
	local combo = fl_game:search(name);
	combo.textcolor = c;
	combo.opacity = c.a;
end

function ����ȫ��͸��(a)
	local c = color4(1,1,1,a);
	�����ı�͸��("����ֵ", c);
	�����ı�͸��("��������", c);
end
g_lianji_fx = 0;
function ������������Ч��(tm)
	tm = tm * 3;
	local tmv = math.sin(tm*math.pi/(g_lianji_time+1))*80;
	if tmv > 35 then
		tmv = 35+(tmv-35)/5;
		g_lianji_fx = 1;
	elseif tmv < 0 then
		g_lianji_c.display = false;
		g_lianji_c2.display = false;
		fl_game:show("������ʱ", false);
		breaktime();
	end
	g_lianji_c.opacity = tmv/35;
	g_lianji_c2.opacity = tmv/35;
	g_lianji_c.movetop = 75 - tmv;
	g_lianji_c2.movetop = 71 - tmv;
end
function ������������(n)
	local newl = getvali("jifen")+n;
	setvali("jifen", newl);
	fl_game:setvalt("����ֵ", "x"..getvali("jifen"));
	if newl > readi("newrecord",0) then
		setvali("newrecord", 1);
		writei("newrecord", newl);
	end
end
function ��������()
	local tm = apptime() - g_combotime;
	g_combotime = apptime();
	print("LIANJIE:"..tm..","..g_lianji_time);
	if tm < g_lianji_time then
		g_combocount = g_combocount + 1;
		if g_combocount > 1 then
			fl_game:setvalt("����ֵ", "+ "..g_combocount);
			local si = g_combocount;
			if si > 15 then
				si = 15;
			end
			������Ч("beiwin"..(si-1));
			interval(50, "������������Ч��", (g_lianji_time+1) * 1000);
			g_lianji_c.display = true;
			g_lianji_c2.display = true;
			g_lianji_c.opacity = 0;
			g_lianji_c2.opacity = 0;
		else
			������������(1);
			return false;
		end
	else
		������������(1);
		g_lianji_c.display = false;
		g_lianji_c2.display = false;
		fl_game:setvalt("����ֵ", "0");
		g_combocount = 0;
		return false;
	end

	
	local combocountt = round(int(g_combocount/2));
	if combocountt > 2 then
		combocountt = 2;
	end
	local combocountg = round(math.pow(int(g_combocount/1.5), 1.5));
	if combocountt > 0 then--g_combocountt then
		fl_game:show("������ʱ", true);
		fl_game:search("������ʱ").action = "ani";
		fl_game:bind_event("onplayover", "������ʱ", "���ؿؼ�");
		local dt = combocountt;--(combocountt-g_combocountt);--*100;
		--print("addtime:"..dt);
		game_time = game_time + dt;
		if game_time > game_time_length then
			game_time = game_time_length;
		end
		g_timeadd = g_timeadd + dt;
		g_combocountt = combocountt;
		����ʱ�����(game_time);
	end
	if combocountg > 0 then --g_combocountg then
		local dt = combocountg;-- - g_combocountg;
		������������(g_combocount);
		g_combocountg = combocountg;
	end
	fl_game:setvalt("������ʱ", "+"..combocountt);
	--combo ��2��ʱ�� round(1��*int(combo����/2),0)
	--combo ��5��ħ�� round(1.5*int(combo����/5),0)
	��������();
	return true;
end
function �޿�������()
	������Ϸ���ص���Ϸ();
end
function ѡ��һ���齫(mj)
	local last_index;
	local index = game_mj[mj.x][mj.y];
	if lastsel_mj~= nil then
		last_index = game_mj[lastsel_mj.x][lastsel_mj.y];
		majiangs[last_index].color = color4(1,1,1,1);
		if last_index ~= index then
			if ���������齫(lastsel_mj, mj, true) then
				return;
			else
				--������Ч("dropno");
			end
			lastsel_mj = nil;
		else
			lastsel_mj = nil;
		end
		--return;
	end
	if index >= 0 then
		������Ч("selmj");
		lastsel_mj = mj;
		last_index = game_mj[lastsel_mj.x][lastsel_mj.y];
		majiangs[last_index].color = color4(0.5,0.5,0.5,1);
		if �����û�״̬ then
			majiangs_sel[0].pos = Pixel(game_mj_beginX + lastsel_mj.x * mjwidth, game_mj_beginY + lastsel_mj.y * mjheight);
			majiangs_sel[0].display = true;
		end
	end
end

��ָ����ֵ = nil;
��ָ���µ� = nil;
function PtInPos(pt, pos1, pos2)
	if pt.x < pos1.x or pt.y < pos1.y or pt.x>pos2.x or pt.y >pos2.y then
		return false;
	end
	return true;
end
function PtInRect(rect,pt)
	if pt.x < rect.left or pt.y < rect.top or pt.x>rect.right or pt.y >rect.bottom then
		return false;
	end
	return true;
end
mouse_down_mj = nil;
mouse_down = nil;
mouse_down_mjs = {};
mouse_down_mjcount = 0;
mouse_dir_x = 0;
mouse_dir_y = 0;
mouse_mj_clamp = 0;
function �����µ��齫(pt)
	if game_begin then
		for i=0,(game_mjcount_w-1) do
			for j=0,(game_mjcount_h-1) do
				if game_mj[i][j] >= 0 then

					if majiangs_exist[game_mj[i][j]] > 0 then
					else
					--print("ERROR:NoDisplay"..i..","..j..",".."|"..game_mj[i][j]);
					end
					local mjrect = majiangs[game_mj[i][j]]:draw_rect();
					mjrect.bottom = mjrect.bottom - mjheight*(8/70);
					if PtInRect(mjrect, pt) then
						if majiangs_disable[game_mj[i][j]]>0 and �����û�״̬ == false then
							fl_game:show("��ʾ��������", true);
							fl_game:search("��ʾ��������").action = "ani";
							fl_game:bind_event("onplayover", "��ʾ��������", "���ؿؼ�");
							return nil;
						end
						return Pixel(i,j);
					end
				end
			end
		end
	end
	return nil;
end
last_movein_mj = nil;
lastwaveplay = -1;
lastdisabled = false;
down_first = false;

function ��ָ����(pt, m)
	pt = fl_region:mousepoint();
	if g_mousedisable == true then
		return;
	end
	local rc = fl_region.rect;
	if point_in(rc, pt) == false then
		return;
	end
	��ָ����ֵ = pt;
	��ָ���µ� = pt;
	mouse_dir_x = 0;
	mouse_dir_y = 0;
	mouse_mj_clamp = 0;
	mouse_down = nil;
	local ptin = Pixel(pt.x - fl_region.left - 20, pt.y - fl_region.top - 20);
	mouse_down_mjs = {};
	mouse_down_mjcount = 0;
	mouse_down_mj = nil;
	down_first = true;
	local mj = �����µ��齫(pt);
	majiangs_sel[0].display = false;
	majiangs_sel[1].display = false;

	if lastsel_mj == mj then
		lastsel_mj = nil;
		last_index = -1;
		if mj ~= nil then
			local lindex = game_mj[mj.x][mj.y];
			majiangs[lindex].color = color4(1,1,1,1);
		end
		return;
	end
	if mj ~= nil then
		mouse_down = mj;
		mouse_down_mj = game_mj[mj.x][mj.y];
		last_movein_mj = Pixel(-1,-1);
		lastwaveplay = -1;
		lastdisabled = false;
		ѡ��һ���齫(mouse_down);
		--��������Ч��(mouse_down);
	end
end
game_mj_can_linear = false;

function ��ָ�ƶ�(pt)
	if ��ָ����ֵ==nil then
		return;
	end
	pt = fl_region:mousepoint();
	local off = pt - ��ָ����ֵ;
	game_mj_can_linear = false;
	local waveplay = 0;
end
function �ж������Ƿ��п�����X(mjpos, mjindex)
	if mjpos.x < (game_mjcount_w-1) then
		for x=(mjpos.x+1),(game_mjcount_w-1) do
			local index = game_mj[x][mjpos.y];
			if index >= 0 then
				if majiangs_disable[index] ~= 0 then
					break;
				end
				if int(index/majiangs_zubie) == int(mjindex/majiangs_zubie) then
					return true;
				end
				break;
			end
		end
	end
	if mjpos.x > 0 then
		for x=1,mjpos.x do
			local index = game_mj[mjpos.x - x][mjpos.y];
			if index >= 0 then
				if majiangs_disable[index] ~= 0 then
					break;
				end
				if int(index/majiangs_zubie) == int(mjindex/majiangs_zubie) then
					return true;
				end
				break;
			end
		end
	end
	return false;
end
function ���ؿ���������()
	majiangs_sel[0].display = false;
	majiangs_sel[1].display = false;
end
function ��ʾ����������(mj1, mj2)
		majiangs_sel[0].pos = Pixel(game_mj_beginX + mj1.x * mjwidth, game_mj_beginY + mj1.y * mjheight);
		majiangs_sel[1].pos = Pixel(game_mj_beginX + mj2.x * mjwidth, game_mj_beginY + mj2.y * mjheight);
		majiangs_sel[0].display = true;
		majiangs_sel[1].display = true;
end
function �ж������Ƿ��п�����Y(mjpos, mjindex)
	--���ؿ���������();
	if mjpos.y < (game_mjcount_h-1) then
		for y=(mjpos.y+1),(game_mjcount_h-1) do
			local index = game_mj[mjpos.x][y];
			if index >= 0 then
				if majiangs_disable[index] ~= 0 then
					break;
				end
				if int(index/majiangs_zubie) == int(mjindex/majiangs_zubie) then
					--��ʾ����������(mjpos, Pixel(mjpos.x,y));
					return true;
				end
				break;
			end
		end
	end
	if mjpos.y > 0 then
		for y=1,mjpos.y do
			local index = game_mj[mjpos.x][mjpos.y - y];
			if index >= 0 then
				if majiangs_disable[index] ~= 0 then
					break;
				end
				if int(index/majiangs_zubie) == int(mjindex/majiangs_zubie) then
					--��ʾ����������(mjpos, Pixel(mjpos.x,y));
					return true;
				end
				break;
			end
		end
	end
	return false;
end
function �����齫λ�����¼���GameMJ()
	local gameover = true;
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			game_mj[x][y] = -1;
		end
	end
	for i=0,(game_mj_count-1) do
		local mjindex = game_mj_index[i];
		local mj = majiangs[mjindex];
		if majiangs[mjindex].display == true then
		local mjpos = �����齫λ��ȡ������(majiangs[mjindex].pos);
		local mjx = mjpos.x;
		local mjy = mjpos.y;
		majiangs_pos[mjindex] = Pixel(mjx*mjwidth+game_mj_beginX, mjy*mjheight+game_mj_beginY);
		if majiangs_exist[mjindex] > 0 then
			if game_mj[mjx][mjy] >= 0 then
				--print("error:"..mjx..","..mjy..","..mjindex);
			end
			if majiangs_disable[mjindex] == 0 then
				gameover = false;
			end
			game_mj[mjx][mjy] = mjindex;
			majiangs[mjindex].layer = mjx+mjy*game_mjcount_w;
		end
		end
	end
	for x=0,(game_mjcount_w-1) do
		for y=0,(game_mjcount_h-1) do
			local mjindex = game_mj[x][y];
			if mjindex >= 0 then
				majiangs_pos[mjindex] = Pixel(x*mjwidth+game_mj_beginX, y*mjheight+game_mj_beginY);
				majiangs[mjindex].pos = majiangs_pos[mjindex];
				majiangs[mjindex].display = true;
			end
		end
	end
	fl_region:sort_draws();
	if gameover then
		g_mousedisable = true;
		cleartime("ʱ����ټ�ʱ");
		timeout(500, "������Ϸ�ȴ�");
	end
	return gameover;
end

function ������Ϸ�ȴ�()
	if getvali("current") == 10 then
		writei("shuangjie", 1);
	elseif getvali("current") == 20 then
		writei("quanjie", 1);
	end
	local nextstar = readi("ok_"..(getvali("current")+1), 0);
	if nextstar == 0 then
		writei("ok_"..(getvali("current")+1), 1);--2=1����
	end
	end_time = localtime();
	������Ч("win");
	cleartime("ʱ����ټ�ʱ");
	timeout(1000, "�ɹ�������Ϸ");
end
fl_game_over = nil;
function ��ʾ��Ϸ������(b)
	if fl_game_over == nil then
		fl_game_over = dlg_load("t_gameover");
	end
	cleartime("ʱ����ټ�ʱ");
	fl_game_over.pos = Pixel(0,0);
	�����Ի���("t_gameover");
	fl_game_over.domodal = true;
	fl_game_over:bind_click("����", "��������Ϸ");
	fl_game_over:bind_click("��һ��", "NextMission");
	fl_game_over.display = true;
	fl_game_over:show("��ɹؿ�", false);
	fl_game_over:show("��ͣ��Ϸ", false);
	fl_game_over:show("�¼�¼����", false);
	fl_game_over:show("��ʱ����", false);
	if insystem("android") then
		ad_show(1, true);
	end
end
function NextMission()
	if fl_game_over ~= nil then
		ad_show(1, false);
		dlg_delete(fl_game_over);
		fl_game_over = nil;
	end
		local oldi = getvali("current");
		local newi = oldi+1;
		if oldi >= 10000 then
			g_savecombocount = g_combocount;
			local mods = getvali("beginsj")+1;
			-- if mods >= 10100 then
				-- mods = 10000;
			-- end
			setvali("beginsj", mods);
			newi = 10000;
			--newi = int(math.random()*4.9) + mods;
			print("NEWI:"..newi);
			local newl = getvali("lianxu")+1;
			setvali("lianxu", newl);
			if newl > readi("lianxu",0) then
				setvali("newrecord", 1);
				writei("lianxu", newl);
			end
			--if (newi%5)==0 then
				--newi = 10000 + int(math.random()*4)*5;
			--end
			game_mjcount_w = int(math.random()*10.6+3);--(int(mods/2)%13);--config:id_i(getvali("current"), "������");
			game_mjcount_h = int(math.random()*5.6+2);--config:id_i(getvali("current"), "������");
			majiangs_zubie = (int(mods/4)*2 % 6)+2;--config:id_i(getvali("current"), "���");
			local num = int(game_mjcount_w*game_mjcount_h/4);
			mjcount_tbl = num*2 + int(num*math.random()/2)*2;--int(mods/5);--ÿ5������һ��
			mjsize_tbl = int((145-35*(game_mjcount_h/7))/5)*5 * 55/100;--config:id_i(getvali("current"), "�齫��С") * 55 / 100;
			timeout(500, "���Լ�������");
		else
			local ri = readi("current");
			if ri < newi then
				writei("current", newi);
			end
			game_mjcount_w = config:id_i(getvali("current"), "������");
			game_mjcount_h = config:id_i(getvali("current"), "������");
			majiangs_zubie = config:id_i(getvali("current"), "���");
			mjcount_tbl = config:id_i(getvali("current"), "����");
			mjsize_tbl = config:id_i(getvali("current"), "�齫��С") * 55 / 100;
		end
		local w = config:id_i(newi, "������");
		if w == 0 then--���û����һ�ؿ��󷵻عؿ��б�
			goto("fl_point");
			return;
		end
		setvali("current", newi);--2=1����
		
		ResetGame();
end
function ���Լ�������()
	g_combotime = apptime();
	g_combocount	=	g_savecombocount;
end
function ��������Ϸ()
	if fl_game_over ~= nil then
		ad_show(1, false);
		dlg_delete(fl_game_over);
		fl_game_over = nil;
		game_mjcount_w = config:id_i(getvali("current"), "������");
		game_mjcount_h = config:id_i(getvali("current"), "������");
		majiangs_zubie = config:id_i(getvali("current"), "���");
		mjcount_tbl = config:id_i(getvali("current"), "����");
		mjsize_tbl = config:id_i(getvali("current"), "�齫��С") * 55 / 100;
		ResetGame();
		return;
	end
end
function ��Ϸ����ʧ��()
	��ʾ��Ϸ������(false);
	local ��ʱ���� = fl_game_over:gsearch("��ʱ����");
	��ʱ����.display = true;
	��ʱ����:bind_click("����", "��Ϸ����");
	fl_game:show("region", false);
	fl_game:show("regionbg", false);
	������Ч("warning");
end
function ˬ����ؽ���()
	��ʾ��Ϸ������(false);
	local �¼�¼���� = fl_game_over:gsearch("�¼�¼����");
	�¼�¼����.display = true;
	�¼�¼����:show("����", false);
	�¼�¼����:show("����ȫ��", false);
	�¼�¼����:show("����ˬ��", false);
	�¼�¼����:show("��ʱ", false);
	�¼�¼����:show("��ʱֵ", false);
	�¼�¼����:bind_click("�˳�", "�رղ��ܷ��عؿ�");
	�¼�¼����:setvali("��ɹؿ�ֵ", getvali("lianxu"));
	�¼�¼����:setvali("��û���ֵ", getvali("jifen"));
	setvali("lianxu", 0);
	setvali("jifen", 0);
	if getvali("newrecord") == 1 then
		setvali("newrecord", 0);
		�¼�¼����:show("����ˬ��", true);
	else
		������Ч("warning");
		�¼�¼����:show("����", true);
	end
	fl_game:show("region", false);
	fl_game:show("regionbg", false);

end
function �ɹ�������Ϸ()
	if getvali("current") >= 10000 and getvali("current") < 11000 then
		NextMission();
		print("ˬ���������");
		return;
	end
	��ʾ��Ϸ������(true);
	local ��ɹؿ� = fl_game_over:gsearch("��ɹؿ�");
	��ɹؿ�.display = true;
	local star1 = config:id_i(getvali("current"), "ʱ������");
	local star2 = config:id_i(getvali("current"), "2��ʱ��");
	local star3 = config:id_i(getvali("current"), "3��ʱ��");
	local second = game_time_length - game_time;--timediff_s(end_time, begin_time) - g_timeadd-1;
	local rs = star1 - second;
	��ɹؿ�:setvalt("��ʱֵ", game_time.."/"..game_time_length);
	��ɹؿ�:enable("star1", false);
	��ɹؿ�:enable("star2", false);
	��ɹؿ�:enable("star3", false);
	��ɹؿ�:bind_click("����", "��Ϸ����");
	��ɹؿ�:bind_click("��һ��", "NextMission");
	local ri = readi("current");
	local newi = getvali("current");
	if ri < newi then
		writei("current", newi);
	end
	local olds = readi("ok_"..getvali("current"));
	local news = 1;
	if getvali("current") < 10000 then
		mj_chanchu = readi("mj_chanchu"..getvali("current"), 0);
	end
	��ɹؿ�:enable("��ʯ", mj_chanchu >= ���ħ����������);
	��ɹؿ�:enable("��ʯֵ", mj_chanchu >= ���ħ����������);
	��ɹؿ�:setvalt("��ʯֵ", mj_chanchu.."/"..���ħ����������);
	��ɹؿ�:enable("��ʱֵ", second <= star3);
	��ɹؿ�:enable("��ʱ", second <= star3);
	--print("gametime:"..game_time..","..second..","..star3);
	if game_time >= star3 and mj_chanchu >= ���ħ���������� then
		��ɹؿ�:enable("star1", true);
		��ɹؿ�:enable("star2", true);
		��ɹؿ�:enable("star3", true);
		news = 4;
	elseif game_time >= star2 then
		��ɹؿ�:enable("star1", true);
		��ɹؿ�:enable("star2", true);
		news = 3;
	else
		��ɹؿ�:enable("star1", true);
		news = 2;
	end
	if news > olds then
		writei("ok_"..getvali("current"), news);
		local mjadd = 0;
		if olds==0 then
			mjadd = (news-olds-1);
		else
			mjadd = news-olds;
		end
		writei("mojing", readi("mojing")+mjadd);
	end
end

function �ж���Χ�Ƿ��п�����(mjfrom)
--�Ƿ������
end

function ClampPos(posx, posy)
	local w = (game_mjcount_w-1) * mjwidth + game_mj_beginX;
	local h = (game_mjcount_h-1) * mjheight + game_mj_beginY;
	if posx < game_mj_beginX then
		posx = game_mj_beginX;
	elseif posx > w then
		posx = w;
	end
	if posy < game_mj_beginY then
		posy = game_mj_beginY;
	elseif posy > h then
		posy = h;
	end
	return Pixel(posx,posy);--int(posx/mjwidth), int(posy/mjheight));
end
function �Զ���λ(v)
	local index = atoi(v);
	local pos = majiangs[index].pos;--;
	local origpos = majiangs_pos[index];
	local xok = false;
	local yok = false;
	if pos.x ~= origpos.x then
		local symx = symbol(pos.x - origpos.x);
		local speed = abs(pos.x - origpos.x) * 2;
		if speed < 80 then
			speed = 80;
		end
		if symx > 0 then
			pos.x = pos.x - symx*speed;
			if pos.x < origpos.x then
				pos.x = origpos.x;
			end
		else
			pos.x = pos.x - symx*speed;
			if pos.x > origpos.x then
				pos.x = origpos.x;
			end
		end
	else
		xok = true;
	end
	if pos.y ~= origpos.y then
		local symy = symbol(pos.y - origpos.y);
		local speed = abs(pos.y - origpos.y) / 2;
		if speed < 80 then
			speed = 80;
		end
		if symy > 0 then
			pos.y = pos.y - symy*speed;
			if pos.y < origpos.y then
				pos.y = origpos.y;
			end
		else
			pos.y = pos.y - symy*speed;
			if pos.y > origpos.y then
				pos.y = origpos.y;
			end
		end
	else
		yok = true;
	end
	if xok and yok then
		breaktime();
		if �Ƿ�����������() == false then
			timeout(100, "�޿�������");
		end
		majiangs[index].pos = origpos;
	else
		majiangs[index].pos = Pixel(pos.x, pos.y);
	end
end
function �ƶ��������Զ�����()
	cleartime("�Զ���λ");
	for mj=0,(mouse_down_mjcount-1) do
		local index = mouse_down_mjs[mj];
		majiangs[index].pos = majiangs_pos[index];
	end
	g_mousedisable = false;
	�����齫λ�����¼���GameMJ();
end
function ��ָ����(pt)
	pt = fl_region:mousepoint();
	local ���¼��� = true;
	if mouse_down_mj ~= nil then
		if mouse_dir_x ~=0 or mouse_dir_y ~=0 then
			if game_mj_can_linear then
				�����齫λ�����¼���GameMJ();
				if mouse_down_mj ~= game_mj[mouse_down.x][mouse_down.y] then
					g_movedisable = true;
				end
			end
			for mj=0,(mouse_down_mjcount-1) do
				local mjindex = mouse_down_mjs[mj];
				--if game_mj[mouse_down.x][mouse_down.y] >= 0 then
				interval_1(50, "�Զ���λ", mjindex, 500);
				���¼��� = false;
			end
			g_mousedisable = true;
			timeout(100, "�ƶ��������Զ�����");
		else
		end
		--
	end
	if mouse_down ~= nil then--(mouse_dir_x ~=0 or mouse_dir_y ~=0) then
		local mj = �����µ��齫(pt);
		if mj ~= nil then
			if �Ƿ���������齫(mouse_down, mj) then
				���������齫(mouse_down, mj, ���¼���);
			end
		end
	end
	mouse_down_mj = nil;
	mouse_dir_x = 0;
	mouse_dir_y = 0;
end

