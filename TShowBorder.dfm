object ShowBorder: TShowBorder
  Left = 0
  Top = 0
  Width = 767
  Height = 548
  AutoScroll = True
  BorderIcons = [biSystemMenu, biMinimize, biMaximize, biHelp]
  Caption = 'TShowBorder'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000010000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000888
    888888888880888888888888888080777777777777707777777777777708870F
    FFFFFFFFFFF0FFFFFFFFFFFFF07887FAAFFFFFFFFFFFFFFFFFFFFFFAAF7887FA
    AAFFFFCCFFFAAFFFCCFFFFAAAF7887FFAAFFCCFFFFAAAAFFFFCCFFAAFF7887FF
    FFACFFFFFFFAAFFFFFFFCAFFFF7887FFFFCAFFFFFFFFFFFFFFFFACFFFF7887FF
    FCFFAFFFFCCCCCCFFFFAFFCFFF7887FFFCFFFAFCCFFFFFFCCFAFFFCFFF7887FF
    FFFFFFAFFFFFFFFFFAFFFFFFFF7887FFFFFFFCFAFFFFFFFFAFCFFFFFFF7887FF
    FFFFFCFFAFFFFFFAFFCFFFFFFF7887FFFFFFCFFFFAFFFFAFFFFCFFFFFF7887FF
    FFAFCFFFFFA99AFFFFFCFAFFFF7887FFFAAACFFFFF9999FFFFFCAAAFFF78000F
    FAAACFFFFF9999FFFFFCAAAFF00087FFFFAFCFFFFFA99AFFFFFCFAFFFF7887FF
    FFFFCFFFFAFFFFAFFFFCFFFFFF7887FFFFFFFCFFAFFFFFFAFFCFFFFFFF7887FF
    CFFFFCFAFFFFFFFFAFCFFFFCFF7887FFCFFFFFAFFFFFFFFFFAFFFFFCFF7887FF
    FCFFFAFCCFFFFFFCCFAFFFCFFF7887FFFCFFAFFFFCCCCCCFFFFAFFCFFF7887FF
    FFCAFFFFFFFAAFFFFFFFACFFFF7887FFFFACFFFFFFAAAAFFFFFFCAFFFF7887FF
    AAFFCCFFFFFAAFFFFFCCFFAAFF7887FAAAFFFFCCFFFFFFFFCCFFFFAAAF7887FA
    AFFFFFFFFFFFFFFFFFFFFFFAAF78870FFFFFFFFFFFF0FFFFFFFFFFFFF0788077
    7777777777707777777777777708088888888888888088888888888888800000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Visible = True
  OnActivate = FormPaint
  OnClick = FormClick
  OnClose = FormClose
  OnDblClick = FormDblClick
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  OnResize = FormPaint
  OnShow = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Image: TImage
    Left = 0
    Top = 63
    Width = 2000
    Height = 2000
    OnClick = ImageClick
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 2000
    Height = 41
    Align = alTop
    TabOrder = 0
    object ZoomInButton: TSpeedButton
      Left = 89
      Top = 10
      Width = 25
      Height = 25
      Hint = #1059#1074#1077#1083#1080#1095#1077#1085#1080#1077' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1103
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33033333333333333F7F3333333333333000333333333333F777333333333333
        000333333333333F777333333333333000333333333333F77733333333333300
        033333333FFF3F777333333700073B703333333F7773F77733333307777700B3
        33333377333777733333307F8F8F7033333337F333F337F3333377F8F9F8F773
        3333373337F3373F3333078F898F870333337F33F7FFF37F333307F99999F703
        33337F377777337F3333078F898F8703333373F337F33373333377F8F9F8F773
        333337F3373337F33333307F8F8F70333333373FF333F7333333330777770333
        333333773FF77333333333370007333333333333777333333333}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = ZoomInButtonClick
    end
    object ScaleLabel: TLabel
      Left = 120
      Top = 18
      Width = 33
      Height = 17
      Hint = #1052#1072#1089#1096#1090#1072#1073
      Alignment = taCenter
      AutoSize = False
      Caption = '1:1'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object ZoomOutButton: TSpeedButton
      Left = 159
      Top = 10
      Width = 25
      Height = 25
      Hint = #1059#1084#1077#1085#1100#1096#1077#1085#1080#1077' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1103
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33033333333333333F7F3333333333333000333333333333F777333333333333
        000333333333333F777333333333333000333333333333F77733333333333300
        033333333FFF3F777333333700073B703333333F7773F77733333307777700B3
        333333773337777333333078F8F87033333337F3333337F33333778F8F8F8773
        333337333333373F333307F8F8F8F70333337F33FFFFF37F3333078999998703
        33337F377777337F333307F8F8F8F703333373F3333333733333778F8F8F8773
        333337F3333337F333333078F8F870333333373FF333F7333333330777770333
        333333773FF77333333333370007333333333333777333333333}
      NumGlyphs = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = ZoomOutButtonClick
    end
    object SpeedButton1: TSpeedButton
      Left = 8
      Top = 10
      Width = 25
      Height = 25
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000120B0000120B00000000000000000000FF00FF0274AC
        0274AC0274AC0274AC0274AC0274AC0274AC0274AC0274AC0274AC0274AC0274
        AC0274ACFF00FFFF00FF0274AC138AC457B7E06BCBF84BBFF74ABFF74ABFF74A
        BFF74ABFF64ABFF74ABFF64BC0F72398CC0274ACFF00FFFF00FF0274AC33AAE0
        2392C489D9FA54C7F854C7F753C7F854C7F754C7F854C7F854C7F853C7F7279D
        CE6ACBE50274ACFF00FF0274AC57CAF80274AC99E3FB5ED1FA5ED1FA5ED1FA5E
        D1FA5ED1FA5FD1FA5ED1F85ED1F82CA1CE99EDF70274ACFF00FF0274AC5ED3FA
        0B81B782D5EF79E0FA6ADCFA69DCFB69DCFB6ADCFB69DCFB69DCFA6ADDFB2FA6
        CF9FF0F70274ACFF00FF0274AC68DAFB2BA4D14AB2D797EBFC74E5FB74E5FB74
        E5FC74E5FC74E5FB74E5FC046B0B33A9CFA3F4F752BBD70274AC0274AC70E3FB
        5CD1EF1184B6FCFFFFB8F4FEBAF4FEBAF4FEBAF4FEB8F4FE046B0B25AA42046B
        0BD4F7FACAF3F70274AC0274AC7AEBFE7AEBFC0A7FB50274AC0274AC0274AC02
        74AC0274AC046B0B38CE6547E77F29B44A046B0B0274AC0274AC0274AC83F2FE
        82F3FE82F3FE83F2FC83F3FE82F3FE83F2FE046B0B2DC0513FDC6E3ED86E46E5
        7B28B04A046B0BFF00FF0274ACFEFEFE89FAFF89FAFE89FAFE8AF8FE8AFAFE04
        6B0B046B0B046B0B046B0B3CD86A2EBF53046B0B046B0B046B0BFF00FF0274AC
        FEFEFE8FFEFF8FFEFF8FFEFF0273A32BA4D12BA4D12BA4D1046B0B35D35E20A7
        3A046B0BFF00FFFF00FFFF00FFFF00FF0274AC0274AC0274AC0274ACFF00FFFF
        00FFFF00FFFF00FF046B0B28C24A046B0BFF00FFFF00FFFF00FFFF00FFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF046B0B17A42B19A730046B
        0BFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FFFF00FF046B0B11A122046B0BFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FF046B0B046B0B046B0B046B0BFF00FFFF00
        FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF046B0B046B0B04
        6B0B046B0BFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF}
    end
    object SpeedButton2: TSpeedButton
      Left = 39
      Top = 10
      Width = 25
      Height = 25
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000120B0000120B00000000000000000000FF00FFFF00FF
        FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFFF00FFFF00FFFF00FFFF00FFFF00FF7F2B287F2B28A18283A18283A18283A1
        8283A18283A18283A182837A1C1C7F2B28FF00FFFF00FFFF00FFFF00FF7F2B28
        CA4D4DB64545DDD4D5791617791617DCE0E0D7DADECED5D7BDBABD76100F9A2D
        2D7F2B28FF00FFFF00FFFF00FF7F2B28C24A4BB14444E2D9D9791617791617D9
        D8DAD9DEE1D3D9DCC1BDC1761111982D2D7F2B28FF00FFFF00FFFF00FF7F2B28
        C24A4AB04242E6DCDC791617791617D5D3D5D8DEE1D7DDE0C6C2C5700F0F962C
        2C7F2B28FF00FFFF00FFFF00FF7F2B28C24A4AB04141EADEDEE7DDDDDDD4D5D7
        D3D5D5D7D9D7D8DACAC2C57E17179E31317F2B28FF00FFFF00FFFF00FF7F2B28
        BF4748B84545BA4C4CBD5757BB5756B64E4EB44949BD5251BB4B4CB54242BF4A
        4A7F2B28FF00FFFF00FFFF00FF7F2B28A33B39B1605DC68684CB918FCC9190CC
        908FCB8988C98988CB9391CC9696BD4B4C7F2B28FF00FFFF00FFFF00FF7F2B28
        BD4B4CF7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7BD4B
        4C7F2B28FF00FFFF00FFFF00FF7F2B28BD4B4CF7F7F7F7F7F7F7F7F7F7F7F7F7
        F7F7F7F7F7F7F7F7F7F7F7F7F7F7BD4B4C7F2B28FF00FFFF00FFFF00FF7F2B28
        BD4B4CF7F7F7BFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFF7F7F7BD4B
        4C7F2B28FF00FFFF00FFFF00FF7F2B28BD4B4CF7F7F7F7F7F7F7F7F7F7F7F7F7
        F7F7F7F7F7F7F7F7F7F7F7F7F7F7BD4B4C7F2B28FF00FFFF00FFFF00FF7F2B28
        BD4B4CF7F7F7BFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFBFF7F7F7BD4B
        4C7F2B28FF00FFFF00FFFF00FF7F2B28BD4B4CF7F7F7F7F7F7F7F7F7F7F7F7F7
        F7F7F7F7F7F7F7F7F7F7F7F7F7F7BD4B4C7F2B28FF00FFFF00FFFF00FFFF00FF
        7F2B28F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F7F77F2B
        28FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF}
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 41
    Width = 2000
    Height = 19
    Align = alTop
    Panels = <
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end>
  end
end
