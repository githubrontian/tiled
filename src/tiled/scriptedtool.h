/*
 * scriptedtool.h
 * Copyright 2019, Thorbjørn Lindeijer <bjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "abstracttiletool.h"

#include <QJSValue>

namespace Tiled {

class BrushItem;
class EditableMap;
class EditableTile;

class ScriptedTool : public AbstractTileTool
{
    Q_OBJECT

    Q_PROPERTY(Tiled::EditableMap *map READ editableMap)
    Q_PROPERTY(Tiled::EditableTile *selectedTile READ editableTile)

public:
    explicit ScriptedTool(QJSValue object, QObject *parent = nullptr);
    ~ScriptedTool() override;

    EditableMap *editableMap() const;
    EditableTile *editableTile() const;

    void activate(MapScene *scene) override;
    void deactivate(MapScene *scene) override;
    void keyPressed(QKeyEvent *) override;
    void mouseEntered() override;
    void mouseLeft() override;
    void mouseMoved(const QPointF &pos, Qt::KeyboardModifiers modifiers) override;
    void mousePressed(QGraphicsSceneMouseEvent *event) override;
    void mouseReleased(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClicked(QGraphicsSceneMouseEvent *event) override;
    void modifiersChanged(Qt::KeyboardModifiers) override;
    void languageChanged() override;
    void populateToolBar(QToolBar *) override;

    static bool validateToolObject(QJSValue value);

protected:
    void mapDocumentChanged(MapDocument *oldDocument, MapDocument *newDocument) override;

    void tilePositionChanged(const QPoint &tilePos) override;
    void updateStatusInfo() override;

    void updateEnabledState() override;

private:
    bool call(const QString &methodName, const QJSValueList &args = QJSValueList());

    QJSValue mScriptObject;
    BrushItem *mBrushItem;
    MapScene *mScene = nullptr;
};

} // namespace Tiled

Q_DECLARE_METATYPE(Tiled::ScriptedTool*)