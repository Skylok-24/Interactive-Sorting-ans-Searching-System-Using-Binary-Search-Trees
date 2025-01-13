#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "src/BST.h"

#define WINDOW_WIDTH 1324
#define WINDOW_HEIGHT 768
#define NODE_RADIUS 25
#define LEVEL_HEIGHT 100

struct Tree* root = NULL;
int selectedOperation = 0;
char inputBuffer[32] = "";
int inputPos = 0;
char messageBuffer[100] = "";
int messageTimer = 0;
int highlightedNode = -1;
float nodeColors[3][3] = {
    {0.3f, 0.6f, 1.0f},
    {0.2f, 0.8f, 0.2f},
    {0.8f, 0.2f, 0.2f}
};

void showMessage(const char* message) {
    strncpy(messageBuffer, message, 99);
    messageBuffer[99] = '\0';
    messageTimer = 100;
}

void drawCircle(float cx, float cy, float r, float* color) {
    const int num_segments = 100;

    glColor4f(0.0f, 0.0f, 0.0f, 0.2f);
    glBegin(GL_TRIANGLE_FAN);
    float cx_shadow = cx + 3;
    float cy_shadow = cy - 3;
    glVertex2f(cx_shadow, cy_shadow);
    for(int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx_shadow + x, cy_shadow + y);
    }
    glEnd();

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();

    glLineWidth(2.0f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawText(float x, float y, const char* text, int centered) {
    void* font = GLUT_BITMAP_9_BY_15;
    float offset = centered ? (strlen(text) * 4.5f) : 0;
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x - offset, y - 5);
    for(int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

void drawButton(float x, float y, float width, float height, const char* text, int highlighted) {
    if (highlighted) {
        glColor3f(0.8f, 0.8f, 0.9f);
    } else {
        glColor3f(0.7f, 0.7f, 0.8f);
    }

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    glLineWidth(2.0f);
    glColor3f(0.4f, 0.4f, 0.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    char buttonText[50];
    if (strcmp(text, "Exit") == 0) {
        sprintf(buttonText, "%s (4)", text);
    } else if (strcmp(text, "Add Node") == 0) {
        sprintf(buttonText, "%s (1)", text);
    } else if (strcmp(text, "Search Node") == 0) {
        sprintf(buttonText, "%s (2)", text);
    } else if (strcmp(text, "Delete Node") == 0) {
        sprintf(buttonText, "%s (3)", text);
    } else {
        strcpy(buttonText, text);
    }

    drawText(x + width/2, y + height/2 + 5, buttonText, 1);
}

void drawLine(float x1, float y1, float x2, float y2) {
    glLineWidth(3.0f);
    glColor4f(0.0f, 0.0f, 0.0f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(x1 + 3, y1 - 3);
    glVertex2f(x2 + 3, y2 - 3);
    glEnd();

    glLineWidth(2.0f);
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawNode(struct Tree* node, float x, float y, float width, int level) {
    if(node == NULL) return;

    if(node->left) {
        drawLine(x, y, x - width/2, y - LEVEL_HEIGHT);
        drawNode(node->left, x - width/2, y - LEVEL_HEIGHT, width/2, level + 1);
    }
    if(node->right) {
        drawLine(x, y, x + width/2, y - LEVEL_HEIGHT);
        drawNode(node->right, x + width/2, y - LEVEL_HEIGHT, width/2, level + 1);
    }

    float* color = nodeColors[node->data == highlightedNode ? 1 : 0];
    drawCircle(x, y, NODE_RADIUS, color);

    char value[10];
    sprintf(value, "%d", node->data);
    drawText(x, y, value, 1);
}

void drawInterface() {
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(0, WINDOW_HEIGHT);
    glVertex2f(200, WINDOW_HEIGHT);
    glVertex2f(200, 0);
    glVertex2f(0, 0);
    glEnd();

    const char* buttonLabels[] = {
        "Add Node",
        "Search Node",
        "Delete Node",
        "Exit"
    };

    for(int i = 0; i < 4; i++) {
        drawButton(10, WINDOW_HEIGHT - 50 - (i * 60), 180, 40,
                  buttonLabels[i], selectedOperation == i + 1);
    }

    if(selectedOperation > 0 && selectedOperation < 4) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(10, WINDOW_HEIGHT - 280);
        glVertex2f(190, WINDOW_HEIGHT - 280);
        glVertex2f(190, WINDOW_HEIGHT - 320);
        glVertex2f(10, WINDOW_HEIGHT - 320);
        glEnd();

        char prompt[50];
        sprintf(prompt, "Value: %s", inputBuffer);
        drawText(20, WINDOW_HEIGHT - 305, prompt, 0);
    }

    if(messageTimer > 0) {
        glColor3f(0.2f, 0.2f, 0.2f);
        drawText(WINDOW_WIDTH/2, 30, messageBuffer, 1);
        messageTimer--;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if(root) {
        drawNode(root, WINDOW_WIDTH/2, WINDOW_HEIGHT - 100, WINDOW_WIDTH/3, 0);
    }

    drawInterface();

    glutSwapBuffers();
}

void processInput(int value) {
    switch(selectedOperation) {
        case 1:
            if(root == NULL || value != root->data) {
                root = insertNode(root, value);
                showMessage("Node added successfully");
                highlightedNode = value;
            } else {
                showMessage("Node already exists");
            }
            break;

        case 2:
            highlightedNode = value;
            showMessage("Searching...");
            searchNode(root, value);
            break;

        case 3:
            if(root) {
                if(value == root->data) {
                    root = deleteNodeWithSuccessor(root, value);
                } else {
                    root = deleteNodeWithPredecessor(root,value);
                }
                showMessage("Node deleted successfully");
            } else {
                showMessage("Tree is empty");
            }
            break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if(selectedOperation > 0 && selectedOperation < 4 && inputPos >= 0) {
        if(key >= '0' && key <= '9' && inputPos < 31) {
            inputBuffer[inputPos++] = key;
            inputBuffer[inputPos] = '\0';
        }
        else if(key == 13 && inputPos > 0) {
            processInput(atoi(inputBuffer));
            selectedOperation = 0;
            inputBuffer[0] = '\0';
            inputPos = 0;
        }
        else if(key == 27) {
            selectedOperation = 0;
            inputBuffer[0] = '\0';
            inputPos = 0;
            highlightedNode = -1;
        }
        else if(key == 8 || key == 127) {
            if(inputPos > 0) {
                inputBuffer[--inputPos] = '\0';
            }
        }
    }
    else {
        switch(key) {
            case '1':
                selectedOperation = 1;
            inputBuffer[0] = '\0';
            inputPos = 0;
            highlightedNode = -1;
            break;
            case '2':
                selectedOperation = 2;
            inputBuffer[0] = '\0';
            inputPos = 0;
            highlightedNode = -1;
            break;
            case '3':
                selectedOperation = 3;
            inputBuffer[0] = '\0';
            inputPos = 0;
            highlightedNode = -1;
            break;
            case '4':
                    freeTree(root);
            exit(0);
            break;
            case 27:
                freeTree(root);
            exit(0);
            break;
        }
    }

    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Binary Tree Visualization");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}