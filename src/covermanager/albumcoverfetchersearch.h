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

#ifndef ALBUMCOVERFETCHERSEARCH_H
#define ALBUMCOVERFETCHERSEARCH_H

#include "config.h"

#include <stdbool.h>

#include <QtGlobal>
#include <QObject>
#include <QList>
#include <QMap>
#include <QPair>
#include <QString>
#include <QImage>
#include <QNetworkAccessManager>

#include "albumcoverfetcher.h"
#include "coversearchstatistics.h"

class CoverProvider;
class CoverProviders;
class NetworkTimeouts;
class RedirectFollower;

// This class encapsulates a single search for covers initiated by an AlbumCoverFetcher.
// The search engages all of the known cover providers.
// AlbumCoverFetcherSearch signals search results to an interested AlbumCoverFetcher when all of the providers have done their part.
class AlbumCoverFetcherSearch : public QObject {
  Q_OBJECT

 public:
  AlbumCoverFetcherSearch(const CoverSearchRequest &request, QNetworkAccessManager *network, QObject *parent);

  void Start(CoverProviders *cover_providers);

  // Cancels all pending requests.  No Finished signals will be emitted, and it is the caller's responsibility to delete the AlbumCoverFetcherSearch.
  void Cancel();

  CoverSearchStatistics statistics() const { return statistics_; }

 signals:
  // It's the end of search (when there was no fetch-me-a-cover request).
  void SearchFinished(const quint64, const CoverSearchResults &results);

  // It's the end of search and we've fetched a cover.
  void AlbumCoverFetched(const quint64, const QUrl &cover_url, const QImage &cover);

 private slots:
  void ProviderSearchFinished(const int id, const CoverSearchResults &results);
  void ProviderCoverFetchFinished(RedirectFollower *reply);
  void TerminateSearch();

 private:
  void AllProvidersFinished();

  void FetchMoreImages();
  float ScoreImage(const QImage &image) const;
  void SendBestImage();

 private:
  static const int kSearchTimeoutMs;
  static const int kImageLoadTimeoutMs;
  static const int kTargetSize;
  static const float kGoodScore;

  CoverSearchStatistics statistics_;

  // Search request encapsulated by this AlbumCoverFetcherSearch.
  CoverSearchRequest request_;

  // Complete results (from all of the available providers).
  CoverSearchResults results_;

  QMap<int, CoverProvider*> pending_requests_;
  QMap<RedirectFollower*, CoverSearchResult> pending_image_loads_;
  NetworkTimeouts* image_load_timeout_;

  // QMap is sorted by key (score).  Values are (result, image)
  typedef QPair<CoverSearchResult, QImage> CandidateImage;
  QMap<float, CandidateImage> candidate_images_;

  QNetworkAccessManager *network_;

  bool cancel_requested_;

};

#endif  // ALBUMCOVERFETCHERSEARCH_H
