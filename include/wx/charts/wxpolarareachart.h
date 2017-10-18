/*
    Copyright (c) 2016-2017 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

/*
    Part of this file were copied from the Chart.js project (http://chartjs.org/)
    and translated into C++.

    The files of the Chart.js project have the following copyright and license.

    Copyright (c) 2013-2016 Nick Downie
    Released under the MIT license
    https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

/// @file

#ifndef _WX_CHARTS_WXPOLARAREACHART_H_
#define _WX_CHARTS_WXPOLARAREACHART_H_

#include "wxchart.h"
#include "wxchartslicedata.h"
#include "wxpolarareachartoptions.h"
#include "wxchartradialgrid.h"
#include "wxchartarc.h"

/// Data for the wxPolarAreaChartCtrl control.
class wxPolarAreaChartData
{
public:
    wxPolarAreaChartData();

    void AppendSlice(const wxChartSliceData &slice);

    const wxVector<wxChartSliceData>& GetSlices() const;

private:
    wxVector<wxChartSliceData> m_slices;
};

/// A polar area chart.
class wxPolarAreaChart : public wxChart
{
public:
    wxPolarAreaChart(const wxPolarAreaChartData &data, const wxSize &size);
    wxPolarAreaChart(const wxPolarAreaChartData &data, 
        const wxPolarAreaChartOptions &options, const wxSize &size);

    virtual const wxPolarAreaChartOptions& GetOptions() const wxOVERRIDE;

private:
    void Add(const wxChartSliceData &slice, const wxSize &size);
    void Add(const wxChartSliceData &slice, size_t index, const wxSize &size);

    static wxDouble GetMinValue(const wxVector<wxChartSliceData> &slices);
    static wxDouble GetMaxValue(const wxVector<wxChartSliceData> &slices);

    virtual void DoSetSize(const wxSize &size) wxOVERRIDE;
    virtual void DoFit() wxOVERRIDE;
    virtual void DoDraw(wxGraphicsContext &gc) wxOVERRIDE;
    virtual wxSharedPtr<wxVector<const wxChartElement*> > GetActiveElements(const wxPoint &point) wxOVERRIDE;

private:
    class SliceArc : public wxChartArc
    {
    public:
        typedef wxSharedPtr<SliceArc> ptr;

        SliceArc(const wxChartSliceData &slice, wxDouble x, wxDouble y,
            wxDouble startAngle, wxDouble endAngle, wxDouble radius);

        void Resize(const wxSize &size);

        wxDouble GetValue() const;

    private:
        wxDouble m_value;
    };

private:
    wxPolarAreaChartOptions m_options;
    wxChartRadialGrid m_grid;
    wxVector<SliceArc::ptr> m_slices;
};

#endif
