#include "Model.h"
#include "View.h"
#include "Controller.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Model model;
    View view;
    Controller controller(model, view);

    controller.start();

    return 0;
}
