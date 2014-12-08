#include "MoveTask.h"

MoveTask::MoveTask(MGroundUnit *m_unit, GameMap *m_map, StiGame::Point m_endPoint) :
    Task("MoveTask")
{
    unit = m_unit;
    map = m_map;
    endPoint = m_endPoint;
    stepSize = unit->getIdentity()->getMovementSpeed();
    caption = "Moving";

    endPointCorrection();
}

void MoveTask::endPointCorrection(void)
{
    int n_x = 0;
    int n_y = 0;

    if(endPoint.getX() < 0)
    {
        n_x = 0;
    }
    else if(endPoint.getX() + unit->getWidth() > map->getWidth() * Tile::TILE_WIDTH)
    {
        n_x = (map->getWidth() * Tile::TILE_WIDTH) - unit->getWidth();
    }
    else
    {
        n_x = endPoint.getX();
    }

    if(endPoint.getY() < 0)
    {
        n_y = 0;
    }
    else if(endPoint.getY() + unit->getHeight() > map->getHeight() * Tile::TILE_HEIGHT)
    {
        n_y = (map->getHeight() * Tile::TILE_HEIGHT) - unit->getHeight();
    }
    else
    {
        n_y = endPoint.getY();
    }

    if(!endPoint.equals(n_x, n_y))
    {
        endPoint = StiGame::Point(n_x, n_y);
    }
}

MoveTask::~MoveTask()
{

}

void MoveTask::doStep(void)
{
    StiGame::Point currentPt (unit->getX(), unit->getY());

    if(!currentPt.equals(&endPoint))
    {
        StiGame::Point currentTilePt (unit->getX() / Tile::TILE_WIDTH, unit->getY() / Tile::TILE_HEIGHT);
        StiGame::MPoint tmpTargetPt (endPoint.getX(), endPoint.getY());
        StiGame::MPoint finalPt;
        bool moveOk = false;
        int initStep = unit->getIdentity()->getMovementStep();
        int moveStep = initStep;
        int _try = 0;
        while(!moveOk)
        {
            int dx = tmpTargetPt.getX() - currentPt.getX();
            int dy = tmpTargetPt.getY() - currentPt.getY();

            int a_dx = abs(dx);
            int a_dy = abs(dy);

            if(dx > 0)
            {
                dx = 1;
            }
            else if(dx < 0)
            {
                dx = -1;
            }

            if(dy > 0)
            {
                dy = 1;
            }
            else if(dy < 0)
            {
                dy = -1;
            }

            int nx = 0;
            int ny = 0;

            //unit direction
            if(dx == 0 || a_dy > a_dx)
            {
                if(dy > 0)
                {
                    unit->setDirection(StiGame::SD_DOWN);
                }
                else
                {
                    unit->setDirection(StiGame::SD_UP);
                }
            }
            else if(dy == 0 || a_dx > a_dy)
            {
                if(dx > 0)
                {
                    unit->setDirection(StiGame::SD_RIGHT);
                }
                else
                {
                    unit->setDirection(StiGame::SD_LEFT);
                }
            }

            if(dx != 0 && dy != 0)
            {
                moveStep = initStep / 2;
            }
            else
            {
                moveStep = initStep;
            }

            nx = currentPt.getX() + dx*moveStep;
            ny = currentPt.getY() + dy*moveStep;
            StiGame::Point pxPt(nx, ny);
            StiGame::Point proTilePt (nx / Tile::TILE_WIDTH, ny / Tile::TILE_HEIGHT);

            if(currentTilePt.equals(&proTilePt))
            {
                if(!map->buildingsContains(&pxPt))
                {
                    finalPt.setPoint(nx, ny);
                    break;
                }
                else
                {
                    dx = (rand() % 3) - 1;
                    dy = (rand() % 3) - 1;

                    tmpTargetPt.setPoint(currentPt.getX() + (dx * Tile::TILE_WIDTH), currentPt.getY() + (dy * Tile::TILE_HEIGHT));

                }
            }
            else
            {

                Tile *proTile = map->get(proTilePt);

                if(proTile->getType() == TT_Normal)
                {
                    finalPt.setPoint(nx, ny);
                    break;
                }
                else
                {
                    //changing the tmpTargetPt for another tile
                    dx = (rand() % 3) - 1;
                    dy = (rand() % 3) - 1;

                    tmpTargetPt.setPoint(currentPt.getX() + (dx * Tile::TILE_WIDTH), currentPt.getY() + (dy * Tile::TILE_HEIGHT));
                }
            }

            _try++;

            if(_try > 1000)
            {
                std::cout << "1000 try hitted !!" << std::endl;
            }
        }

        int _dx = abs(endPoint.getX() - finalPt.getX());
        int _dy = abs(endPoint.getY() - finalPt.getY());

        if(_dx <= moveStep && _dy <= moveStep)
        {
            unit->setPoint(&endPoint);
        }
        else
        {
            unit->setPoint(&finalPt);
        }
    }
    else
    {
        terminated = true;
    }
}
