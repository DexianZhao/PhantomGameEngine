mission_pagecount = 10;
MAX_CLICK_REGION = 20*20;
MISSION_WIDTH	=	7;
MISSION_PAGE_COUNT2 = MISSION_WIDTH*4;
MAX_MISSIONS = mission_pagecount*MISSION_PAGE_COUNT2;

function ������ҳ��()
	������Ч("click");
	timeout_1(500, "������һ������", "fl_main");

end

function oncall(name,params, params2)
	if name=="jifen_score" then
		local n = atoi(params);
		local rjifen = readi("jifen_score");
		if n > rjifen then
			local add = n - rjifen;
			writei("mojing", readi("mojing",0)+add);
			writei("jifen_score", n);
		end
		������ʯ��ʾ();
	elseif name == "buy_ok" then
		print("����ɹ�����ʯ:"..params..",trans:"..params2);
		if params == "mjlink.buygem" then
			if readi("trans_"..params2, 0) == 0 then
				writei("trans_"..params2, 1);
				writei("mojing", readi("mojing",0)+10000);--����ɹ�����10000��ʯ=6��Ǯ
			else
				print("�Ѿ���ӹ��ˣ������ظ��������");
			end
			������ʯ��ʾ();
		end
	end
end
function ��������ʯ()--�������ǽ
	������Ч("click");
	ad_show(2, true);
end

sh_snd_volume = 1;--������������
sh_snd_max = true;--���������Ƿ����
function ��ʼ�������ֱ�С()
	if sh_snd_max then
		interval(200, "�������ֱ�С", 5000);
		sh_snd_max = false;
	end
end
sh_bg_music = nil;--��������
sh_bg_music_name = "";
sh_bg_audio_on = readi("audioon", 1);
function ���ű�������(name)
	sh_bg_music_name = name;
	if sh_bg_music ~= nil then
		stopsnd(sh_bg_music);
	end
	if readi("musicon") == 1 then
		sh_bg_music = playmp3(name);
		setsndvolume(sh_bg_music, sh_snd_volume);
	end
end
function ������һ������(v)
	goto(v);
end
function ������Ч(name)
	if sh_bg_audio_on == 1 then
		playwave(name);
	end
end
function �������ֱ�С()
	sh_snd_volume = sh_snd_volume - 0.01;
	if sh_snd_volume <= 0.85 then
		sh_snd_volume = 0.85;
		cleartime("�������ֱ�С");
	end
	if sh_bg_music ~= nil then
		setsndvolume(sh_bg_music, sh_snd_volume);
	end
end
function �������ֱ��()
	sh_snd_volume = sh_snd_volume + 0.01;
	if sh_snd_volume >= 1 then
		sh_snd_volume = 1;
		cleartime("�������ֱ��");
		sh_snd_max = true;
	end
	if sh_bg_music ~= nil then
		setsndvolume(sh_bg_music, sh_snd_volume);
	end
end

function alert(caption, msg, script)
	msgbox(caption, msg, "ok", script);
	�����Ի���("msgbox");
end
dlg_config = nil;
function �ر�ϵͳ����()
	������Ч("quit");
	if dlg_config ~= nil then
		dlg_delete(dlg_config);
		dlg_config = nil;
	end
end
function �ر�����()
	if dlg_config:getvali("musicon") == 1 then
		writei("musicon", 1);
		if sh_bg_music == nil then
			���ű�������(sh_bg_music_name);
		end
	else
		writei("musicon", 0);
		if sh_bg_music ~= nil then
			stopsnd(sh_bg_music);
			sh_bg_music = nil;
		end
	end
end
function �ر���Ч()
	sh_bg_audio_on = dlg_config:getvali("audioon");
	writei("audioon", sh_bg_audio_on);
end
function ��ϵͳ����()
	������Ч("window");
	dlg_config = dlg_load("config");
	dlg_config.display = true;
	dlg_config:setvali("musicon", readi("musicon", 1));
	dlg_config:setvali("audioon", readi("audioon", 1));
	dlg_config:bind_click("close", "�ر�ϵͳ����");
	dlg_config:bind_click("musicon", "�ر�����");
	dlg_config:bind_click("audioon", "�ر���Ч");
	dlg_config.domodal = true;
	�����Ի���("config");
end

dlg_scale_begin = 1.0;
dlg_scale_turn = 0;
function �����Ի���(name)
	
	dlg_scale_turn = 0;
	local dlg = dlg_search(name);
	dlg_scale_begin = 0.1;
	dlg.center = Pixel(480, 320);
	dlg.scalef = dlg_scale_begin;
	interval_1(50, "�����Ի���ѭ��", name, 100000);
end

function �����Ի���ѭ��(name)
	if dlg_scale_turn == 0 then
		dlg_scale_begin = dlg_scale_begin + 0.35;
		if dlg_scale_begin > 1.2 then
			dlg_scale_begin = 1.2;
			dlg_scale_turn = 1;
		end
	else
		dlg_scale_begin = dlg_scale_begin - 0.15;
		if dlg_scale_begin < 1 then
			dlg_scale_begin = 1;
			cleartime("�����Ի���ѭ��");
		end
	end
	local dlg = dlg_search(name);
	dlg.scalef = dlg_scale_begin;
end

function ResetScale(cname)
	local ctrl = shgame:search(cname);
	ctrl.scale = 1;
end

