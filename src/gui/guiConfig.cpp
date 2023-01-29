#include "../../imgui/imgui.h"
#include "gui.h"
#include "guiConfig.h"
#include "../config.h"


void styles::setup() {
	// Setting styles
	ImGuiStyle* style = &ImGui::GetStyle();

	// Own colours
	ImColor lightBlue = ImColor(58, 169, 255, 255);
	ImColor darkBlue = ImColor(24, 31, 42, 255);
	ImColor midBlue = ImColor(32, 44, 60, 255);

	// Frame and border
	style->FramePadding = ImVec2(8, 6);
	style->FrameBorderSize = 0.5f;
	style->Colors[ImGuiCol_Border] = ImVec4(0.22f, 0.66f, 1.f, 1.0f);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(58, 169, 255, 255);
	style->FrameRounding = 5.f;

	// Button Styles
	style->ButtonTextAlign = ImVec2(0.5, 0.5);
	style->Colors[ImGuiCol_Button] = darkBlue;
	style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 40, 55, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(31, 40, 55, 255);

	// Background
	style->Colors[ImGuiCol_WindowBg] = darkBlue;

	// Checkboxes
	style->Colors[ImGuiCol_FrameBg] = midBlue;
	style->Colors[ImGuiCol_FrameBgHovered] = midBlue;
	style->Colors[ImGuiCol_CheckMark] = lightBlue;

}

void render::Main() {
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 80);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(105, 199, 255, 255)));

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	if (ImGui::Button("Glow", ImVec2(65, 60))) {
		gui::tab_c = 1;
	}
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	if (ImGui::Button("Aim", ImVec2(65, 60))) {
		gui::tab_c = 2;
	}
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	if (ImGui::Button("Misc", ImVec2(65, 60))) {
		gui::tab_c = 3;
	}

	ImGui::PopStyleColor();
	ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 10);
	ImGui::NextColumn();

	// Menus
	Glow();
	Aim();
	Misc();

	ImGui::Columns();
}

void render::Glow() {
	if (gui::tab_c == 1) {
		ImGui::Checkbox("Glow esp", &config::toggle_glow);
		if (config::toggle_glow) {
			ImGui::Indent(20.f);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Health based glow", &config::health_based);
			ImGui::Spacing();
			ImGui::Spacing();
			if (!config::health_based) {
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::PushItemWidth(200.f);
				ImGui::ColorEdit3("WallHack colour", (float*)&config::colours);
			}
			ImGui::Unindent(20.f);
		}
		ImGui::Spacing();
		// Colour picker CHAMS
		ImGui::Checkbox("Chams", &config::toggle_chams);
		if (config::toggle_chams) {
			ImGui::Indent(20.f);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::ColorEdit3("Chams colour", (float*)&config::chams_colours);
			ImGui::Spacing();
			ImGui::SliderFloat("Brightness", &config::chams_brightness, 0.f, 20.f);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Unindent(20.f);
		}
	}
}
void render::Aim() {
	if (gui::tab_c == 2) {
		ImGui::Checkbox("Trigger bot", &config::toggle_trigger);
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Checkbox("Recoil Control", &config::toggle_rcs);
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Checkbox("Aim bot", &config::toggle_aim);
		if (config::toggle_aim) {
			ImGui::Indent(20.f);
			ImGui::SliderFloat("FOV", &config::aimbot_fov, 0.5f, 5.f);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SliderFloat("Snap time", &config::aimbot_snap, 0.7f, 5.f);
			ImGui::Unindent(20.f);
		}
	}
}

void render::Misc() {
	if (gui::tab_c == 3) {
		ImGui::Checkbox("Bunny Hop", &config::toggle_bhop);
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Checkbox("Anti flash", &config::toggle_flash);
	}
}
