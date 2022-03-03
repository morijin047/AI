#include <SDL.h>
#include "lib_Point/Point.h"
#include <vector>
#include <time.h>
#include "Perceptron.h"
SDL_Window* win;
SDL_Renderer* render;
int width = 800, height = 600;
bool classeCandidat(double u, double v, double a, double b, double c);

int main(int argc, char** args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &render);
    srand(time(NULL));
    double a = rand() % 100 + 1;
    double b = -(rand() % 100 + 1);
    double c = 0;
    std::vector<Point*> points;
    const int nbPoints = 250;
    Perceptron* p = new Perceptron(2);
    int expected[nbPoints];
    for (int i = 0; i < nbPoints; i++) {
        double x = rand() % width;
        double y = rand() % height;
        Point* pts = new Point(x, y);
        points.push_back(pts);
        if (classeCandidat(points[i]->x, points[i]->y, a, b, c)) {
            expected[i] = 1;
        }
        else {
            expected[i] = -1;
        }
    }
    SDL_Event event;
    while (isRunning) {
        //Nettoyer la fenêtre
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        //dessin des différents objet dans la fenêtre
        for (int i = 0; i < points.size(); i++) {
            if (expected[i] == 1) {
                points[i]->draw(render, { 0, 255, 0, 255 }, 10);
            }
            else {
                points[i]->draw(render, { 255, 0, 0, 255 }, 10);
            }
        }
        double Ydroite1 = -c / b;
        double Ydroite2 = -(a * width + c) / b;
        SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
        SDL_RenderDrawLine(render, Ydroite1, 0, width, Ydroite2);
        bool AllExpected = true;
        do {
            for (int i = 0; i < points.size(); i++) {
                std::vector<double> X;
                X.push_back(points[i]->x);
                X.push_back(points[i]->y);
                bool output = p->learn(X, expected[i]);
                double Ymin = -p->getTeta() / p->getWy();
                double Ymax = -(p->getWx() * width + p->getTeta()) / p->getWy();
                SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
                SDL_RenderDrawLine(render, Ymin, 0, width, Ymax);
                if (!output)
                    AllExpected = false;
                else
                    AllExpected = true;
            }
        } while (!AllExpected);
        SDL_Delay(15);
        //mise a jour de l'écran
        SDL_RenderPresent(render);
    }
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
bool classeCandidat(double u, double v, double a, double b, double c) {
    bool signe = false;
    if (a * u + b * v + c >= 0)
        signe = true;
    return signe;
}
