#ifndef POINTSUICOMPONENT_H
#define POINTSUICOMPONENT_H

#include "UIElement.h"
#include "../../../../Engine/UI/Text.h"

class PointsUIComponent : public UIElement {
public:
    PointsUIComponent() = default;
    ~PointsUIComponent() = default;

public:
    void Initialise();
    void Update(int points);

private:
    void UpdatePoints(int points);

private:
    Text m_pointsText;

    int m_pointsLastUpdate = 0;
};

#endif