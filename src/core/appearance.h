/*
 * Strawberry Music Player
 * This file was part of Clementine.
 * Copyright 2012, David Sansome <me@davidsansome.com>
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

#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "config.h"

#include <QObject>
#include <QColor>
#include <QPalette>

class Appearance : public QObject {
 public:
  explicit Appearance(QObject *parent = nullptr);
  // Load the user preferred theme, which could the default system theme or a custom set of colors that user has chosen
  void LoadUserTheme();
  void ResetToSystemDefaultTheme();
  void ChangeForegroundColor(const QColor &color);
  void ChangeBackgroundColor(const QColor &color);

  static const char *kSettingsGroup;
  static const char *kUseCustomColorSet;
  static const char *kForegroundColor;
  static const char *kBackgroundColor;
  static const QPalette kDefaultPalette;

 private:
  QColor foreground_color_;
  QColor background_color_;
};

#endif  // APPEARANCE_H

