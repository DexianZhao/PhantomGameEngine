#define	��ʼ��	oninit
#include "fl_base.lua"

fl_shop = nil;
function oninit()
	fl_shop = dlg_load("t_shop");
	fl_shop:enable("background", true);
	fl_shop:bind_click("close", "������ҳ��");
	fl_shop:bind_click("��ħ��", "��ħ��");
	fl_shop:bind_click("ȥ���", "ȥ���");
end

function ��ħ��()
	������Ч("click");
end
function ȥ���()
	������Ч("click");
end
