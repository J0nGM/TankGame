#ifndef TANK_IMGUIHANDLER_HPP
#define TANK_IMGUIHANDLER_HPP

struct ImGuiContext;
struct GLFWwindow;
class game_manger;

class imgui_handler {
private:
    ImGuiContext* context_;
    bool initialized_ {false};


public:
    imgui_handler();
    ~imgui_handler();

    void init(GLFWwindow* window);
    void begin_frame();
    void render_ui(game_manger& game);
    void end_frame();
    void shutdown();
    void game_over_menu(bool& restart_game, bool& quit_game);
    void victory_menu(bool& next_level, bool& quit_game);

};

#endif //TANK_IMGUIHANDLER_HPP