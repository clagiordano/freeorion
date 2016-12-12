#ifndef _TechTreeWnd_h_
#define _TechTreeWnd_h_

#include <GG/Wnd.h>
#include "../universe/Enums.h"

class Tech;
class EncyclopediaDetailPanel;

/** Returns a browse wnd for tech panels */
boost::shared_ptr<GG::BrowseInfoWnd> TechPanelRowBrowseWnd(const std::string& tech_name, int empire_id);

/** Contains the tech graph layout, some controls to control what is visible in
  * the tech layout, the tech navigator, and the tech detail window. */
class TechTreeWnd : public GG::Wnd {
public:
    typedef boost::signals2::signal<void (const std::string&)>                      TechSignalType;
    typedef boost::signals2::signal<void (const std::string&,
                                          const GG::Flags<GG::ModKey>&)>            TechClickSignalType;
    typedef boost::signals2::signal<void (const std::vector<std::string>&, int)>    QueueAddTechsSignalType;

    /** \name Structors */ //@{
    /** TechTreeWnd contructor is usually called before client has
        access to techs.  Attempting to show the tech tree takes a long
        time and generates errors.  If \p initially_hidden is true then the
        tech categories are not parsed until the first time Show() is
        called, speeding up the constructor and preventing spurious errors.*/
    TechTreeWnd(GG::X w, GG::Y h, bool initially_hidden = true);
    ~TechTreeWnd();
    //@}

    /** \name Accessors */ //@{
    double                  Scale() const;
    std::set<std::string>   GetCategoriesShown() const;
    std::set<TechStatus>    GetTechStatusesShown() const;
    bool                    PediaVisible();
    //@}

    //! \name Mutators //@{
    virtual void    SizeMove(const GG::Pt& ul, const GG::Pt& lr);
    void            Update();
    void            Clear();
    void            Reset();
    void            SetScale(double scale);

    virtual void    Show(bool children = true);
    void            ShowCategory(const std::string& category);
    void            ShowAllCategories();
    void            HideCategory(const std::string& category);
    void            HideAllCategories();
    void            ToggleAllCategories();

    void            ShowStatus(const TechStatus status);
    void            HideStatus(const TechStatus status);

    void            ToggleViewType(bool show_list_view);
    void            ShowTreeView();
    void            ShowListView();

    void            CenterOnTech(const std::string& tech_name);
    void            SetEncyclopediaTech(const std::string& tech_name);
    void            SelectTech(const std::string& tech_name);

    void            ShowPedia();
    void            HidePedia();
    void            TogglePedia();
    //@}

    mutable TechSignalType          TechBrowsedSignal;
    mutable TechSignalType          TechSelectedSignal;
    mutable QueueAddTechsSignalType AddTechsToQueueSignal;

private:
    class TechTreeControls;
    class LayoutPanel;
    class TechListBox;

    void    TechBrowsedSlot(const std::string& tech_name);
    void    TechLeftClickedSlot(const std::string& tech_name,
                                const GG::Flags<GG::ModKey>& modkeys);
    void    TechRightClickedSlot(const std::string& tech_name,
                                 const GG::Flags<GG::ModKey>& modkeys);
    void    TechDoubleClickedSlot(const std::string& tech_name,
                                  const GG::Flags<GG::ModKey>& modkeys);
    void    TechPediaDisplaySlot(const std::string& tech_name);

    void    InitializeWindows();

    TechTreeControls*           m_tech_tree_controls;
    EncyclopediaDetailPanel*    m_enc_detail_panel;
    LayoutPanel*                m_layout_panel;
    TechListBox*                m_tech_list;

    /// If m_init_flag is true tech categories are not parsed until the
    /// first time Show() is called.  TechTreeWnd is constructed before the
    /// tech categories are available to be parsed.
    bool                        m_init_flag;
};

#endif // _TechTreeWnd_h_
