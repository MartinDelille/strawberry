/*
 * Strawberry Music Player
 * This file was part of Clementine.
 * Copyright 2010, David Sansome <me@davidsansome.com>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include "config.h"

#include <stdbool.h>

#include <QObject>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QApplication>
#include <QVariant>
#include <QString>
#include <QStringBuilder>
#include <QPainter>
#include <QStyle>
#include <QRect>
#include <QStyleOptionProgressBar>

#include "progressitemdelegate.h"

ProgressItemDelegate::ProgressItemDelegate(QObject *parent)
  : QStyledItemDelegate(parent)
{
}

void ProgressItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

  bool ok = false;
  int progress = index.data().toInt(&ok);

  if (ok) {
    QStyleOptionProgressBar opt;
    opt.rect = option.rect;
    opt.minimum = 0;
    opt.maximum = 100;
    opt.progress = progress;
    opt.text = QString::number(progress) + "%";
    opt.textVisible = true;

    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &opt, painter);
  }
  else {
    QStyledItemDelegate::paint(painter, option, index);
  }

}

