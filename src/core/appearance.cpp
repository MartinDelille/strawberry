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

#include "config.h"

#include <stdbool.h>

#include <QApplication>
#include <QObject>
#include <QVariant>
#include <QPalette>
#include <QColor>
#include <QSettings>

#include "appearance.h"
#include "settings/appearancesettingspage.h"

const char *Appearance::kUseCustomColorSet = "use-custom-set";
const char *Appearance::kForegroundColor = "foreground-color";
const char *Appearance::kBackgroundColor = "background-color";

const QPalette Appearance::kDefaultPalette = QPalette();

Appearance::Appearance(QObject *parent) : QObject(parent) {

  QSettings s;
  s.beginGroup(AppearanceSettingsPage::kSettingsGroup);
  QPalette p = QApplication::palette();
  background_color_ = s.value(kBackgroundColor, p.color(QPalette::WindowText)).value<QColor>();
  foreground_color_ = s.value(kForegroundColor, p.color(QPalette::Window)).value<QColor>();

}

void Appearance::LoadUserTheme() {

  QSettings s;
  s.beginGroup(AppearanceSettingsPage::kSettingsGroup);
  bool use_a_custom_color_set = s.value(kUseCustomColorSet).toBool();
  if (!use_a_custom_color_set) return;

  ChangeForegroundColor(foreground_color_);
  ChangeBackgroundColor(background_color_);

}

void Appearance::ResetToSystemDefaultTheme() {
  QApplication::setPalette(kDefaultPalette);
}

void Appearance::ChangeForegroundColor(const QColor &color) {

  // Get the application palette
  QPalette p = QApplication::palette();

  // Modify the palette
  p.setColor(QPalette::WindowText, color);
  p.setColor(QPalette::Text, color);

  // Make the modified palette the new application's palette
  QApplication::setPalette(p);
  foreground_color_ = color;

}

void Appearance::ChangeBackgroundColor(const QColor &color) {

  // Get the application palette
  QPalette p = QApplication::palette();

  // Modify the palette
  p.setColor(QPalette::Window, color);
  p.setColor(QPalette::Base, color);

  // Make the modified palette the new application's palette
  QApplication::setPalette(p);
  background_color_ = color;

}

