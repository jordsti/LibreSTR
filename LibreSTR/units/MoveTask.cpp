#include "MoveTask.h"
#include "UnitPath.h"

MoveTask::MoveTask(MGroundUnit *m_unit, GameMap *m_map, StiGame::Point m_endPoint) :
    Task("MoveTask")
{
    waiting = true;
    unit = m_unit;

    map = m_map;
    endPoint.setPoint(&m_endPoint);
    stepSize = unit->getIdentity()->getMovementSpeed();
    caption = "Moving";

    //debug purpose
    path = nullptr;
    endPointCorrection();

    thread = new UnitPathThread(this, StiGame::Point(m_unit->getX(), m_unit->getY()), StiGame::Point(&endPoint));
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
        endPoint.setPoint(n_x, n_y);
    }
}

MoveTask::~MoveTask()
{

}

void MoveTask::doStep(void)
{
    if(waiting)
    {
        std::cout << "Waiting on thread to terminate..." << std::endl;
        return;
    }
    else
    {
        clearThread();
    }

    if(path == nullptr)
    {
        return;
    }

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
        if(path->moveToNext())
        {
            endPoint.setPoint(path->getCurrent()->point());
        }
        else
        {
            delete path;
            path = nullptr;
            terminated = true;
        }
    }
}

void MoveTask::setEndPoint(StiGame::Point m_endPoint)
{
    if(path != nullptr)
    {
        delete path;
    }

    endPoint.setPoint(&m_endPoint);
    endPointCorrection();
    //path = UnitPath::FindPath(StiGame::Point(unit), StiGame::Point(&m_endPoint), map);

    if(thread == nullptr)
    {
        waiting = true;
        thread = new UnitPathThread(this, StiGame::Point(unit->getX(), unit->getY()), StiGame::Point(&endPoint));
    }
}


ITileMap* MoveTask::getMap(void)
{
    return map;
}

StiGame::Point* MoveTask::getEndPoint(void)
{
    return &endPoint;
}

void MoveTask::setUnitPath(UnitPath *m_path)
{
    if(path != nullptr)
    {
        delete path;
        path = nullptr;
    }
    path = m_path;

    if(path != nullptr)
    {
        //end point become the second points of the path
        if(path->moveToNext())
        {
            endPoint.setPoint(path->getCurrent()->point());
            if(waiting)
            {
                waiting = false;
            }
        }
        else
        {
            terminated = true;
        }
    }
    else
    {
        terminated = true;
    }
}


void MoveTask::clearThread(void)
{
    if(thread != nullptr)
    {
        delete thread;
        thread = nullptr;
    }
}
