object PressWin: TPressWin
  Left = 0
  Top = 0
  Caption = 'PressWin'
  ClientHeight = 779
  ClientWidth = 745
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000888
    888888888880888888888888888080777777777777707777777777777708870F
    FFFFFFFFFFF0FFFFFFFFFFFFF07887FFFFFFFFFFFFFFFFFFFFFFFFFFFF7887FF
    FF00000000000000000000FFFF7887FFFF0BBB0C00BBBBBBBBBBB0FFFF7887FF
    FF0BB00CC000000BBBBBB0FFFF7887FFFF0000CCCCCCCC0BBBBBB0FFFF7887FF
    FF0CCCCCCCCCCC000000B0FFFF7887FFFF0CCCCC000CCCCCCCC000FFFF7887FF
    FF0CCCCC0BB00CC0000000FFFF7887FFFF0C00000BBBB000BBBBB0FFFF7887FF
    FF0C0BBBBBBBBBBB000000FFFF7887FFFF000BBBBBB000000CCCC0FFFF7887FF
    FF0BBB000000CCCCCCCC00FFFF7887FFFF00000CCCCCCCCCC00000FFFF78000F
    FF0CCCCCC000000000BBB0FFF00087FFFF0CCC0000BBBBBBBBBBB0FFFF7887FF
    FF00000BBBBBBBBBBBBBB0FFFF7887FFFF00BBBBBBBBBBBBBBB000FFFF7887FF
    FF0BBBBBBBB000000000C0FFFF7887FFFF0BBBB00000CCCCCCCCC0FFFF7887FF
    FF0BBB00CCCCCCCCCCCCC0FFFF7887FFFF00000CCCCCCCC0000000FFFF7887FF
    FF0CCCCCCC000000BBBBB0FFFF7887FFFF0CCCCCCC0BBBBBBBBBB0FFFF7887FF
    FF00000000000000000000FFFF7887FFFFFFFFFFFFFFFFFFFFFFFFFFFF7887FF
    FFFFFFFFFFFFFFFFFFFFFFFFFF78870FFFFFFFFFFFF0FFFFFFFFFFFFF0788077
    7777777777707777777777777708088888888888888088888888888888800000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Visible = True
  WindowState = wsMinimized
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Image: TImage
    Left = 0
    Top = 60
    Width = 1000
    Height = 1000
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 745
    Height = 41
    Align = alTop
    TabOrder = 0
    ExplicitLeft = -255
    ExplicitWidth = 1000
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
    object btnPrev: TSpeedButton
      Left = 96
      Top = 10
      Width = 25
      Height = 25
      GroupIndex = 1
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000120B0000120B00000000000000000000FF00FFFF00FF
        FF00FFFF00FFFF00FF521E156B25087D2C057E2D056D2607551F13FF00FFFF00
        FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF552117552117BF5C15E19855EF
        BD8AF0BF8CE29D5BC26218541F16541F16FF00FFFF00FFFF00FFFF00FFFF00FF
        6C290EAF4704EBB179FFFEF8FEF8F4F2DAC4F2D9C2FCF6F0FFFFFCEEBA87B64E
        07602311FF00FFFF00FFFF00FF732D0DB04602F4D0ABFFFEFED78E50C05308BA
        4500BA4600C05307D48443FCF7F0F8DDBDB64D05541F16FF00FFFF00FF732D0D
        E6AB72FFFFFFCF762CB73F00BB4800BF5103BC4A00BA4600B63D00CC7227FCF8
        F3EFBC88541F16FF00FF893406C05C11FFFCFAE1A46AC04B00C65D0CEABF96D1
        7F37B84100BB4800E2AD7AD3823CD18039FFFFFFC16016551F139A3B02DD9554
        FFFFFFD16F1FD47729F4DAC1FFFFFFD58138C4570BEAC29DFFFFFFD78C4BBC4A
        00FCF8F3E29D5A6D2607A94403EBBB8AFBEDDEE19856FBF3EAFFFFFFFFFEFEE3
        A972F6E3CEFFFFFFFFFFFFD78E4DB73F00F2DAC2EFC08E7D2C04B04A06EEBF90
        FCF0E6E79D5AFAE6D1FFFFFFFFFFFFE5A76DF0CEACFFFFFFFFFFFFD78E4CB740
        00F3DEC7EFBD8A7B2C04B04905E9AA6EFFFFFFEBA05AEB994FF8D8B8FFFFFFE5
        9E5DD16A17E7B280FFFFFFD88F4DBD4C01FEFBF8E097526B2408AD4502DD893F
        FFFCF8FAD7B4F4A65DF0A158F6CBA3E7A466D77322CB600EDE9A5DCE782ED78C
        4BFFFFFEBD5A10521F16FF00FFB24701F8CEA5FFFFFFFED1A5F6A75FEB9649E2
        8A3DD97929CF6715C04B00D07930FFFFFFEAAF73501F18FF00FFFF00FFB24701
        E0873BFEE5CBFFFFFFFAD5B2EDA562E28A3FD97B2DD4782AE1A46CFFFFFFF3CC
        A4AC4402501F18FF00FFFF00FFFF00FFB64C04DE873BF8CEA3FFFAF3FFFFFFFE
        F6EEFCF3EAFFFFFFFEF7EEE6A56AAC44035A2214FF00FFFF00FFFF00FFFF00FF
        FF00FFAF4501AF4501DC8840E9A76CEEBB89EBB581DC914DBD590F5D23155D23
        15FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFA34103A54507A6
        46089E40068B3505752D0CFF00FFFF00FFFF00FFFF00FFFF00FF}
      OnClick = btnPrevClick
      OnMouseLeave = btnPrevClick
    end
    object btnNext: TSpeedButton
      Left = 159
      Top = 10
      Width = 25
      Height = 25
      GroupIndex = 1
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000120B0000120B00000000000000000000FF00FFFF00FF
        FF00FFFF00FFFF00FF7D2C056B2508521E15551F136D26077E2D05FF00FFFF00
        FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF893204552117BF5C15E19855EF
        BD8AF0BF8CE29D5BC26218541F16903503FF00FFFF00FFFF00FFFF00FFFF00FF
        6C290EAF4704EBB179FFFEF8FEF8F4F2DAC4F2D9C2FCF6F0FFFFFCEEBA87B64E
        07602311FF00FFFF00FFFF00FF9A3800B04602F4D0ABFEFCFAD78C4EC05409BA
        4600BA4500BF5206D48644FCF8F4F8DDBDB64D05903502FF00FFFF00FF732D0D
        E6AB72FFFFFFD17E35B73F00BB4700BB4900BF5003BB4600B63E00C96A1EFCF8
        F6EFBC88541F16FF00FFA94403C05C11FFFCFADE9A5DD98C48E5B07EC15303BB
        4600D07B33E6B78BBD4D03B53A00D58A46FFFFFFC160167D2C049A3B02DD9554
        FFFFFFD06E1EE2A166FFFFFFEEC7A1C75C0CD17D33FFFFFFEECEAFC2580FBC4B
        01FCF8F4E29D5A6D2607893406EBBB8AFBF0E7D77322E9AD75FFFFFFFFFFFFF4
        DEC9E1A167FFFEFEFFFFFFF8EBDDCA6B21F0D4B8EFC08E551F139A3B02EEBF90
        FCF4EBE08435EEB783FFFFFFFFFFFFF3D0B0E2A166FFFFFFFFFFFFF0D4B8C560
        15F2D9BFEFBD8A521F16A94403E9AA6EFFFFFFEB9F58F3C292FFFFFFF2C79DD9
        7725E19754FFFFFFE7B78ABC4A03BF4F03FEFBFAE097526B2408AD4502DD893F
        FFFCF8FAD3ACFAC592F7C99CE99244E08232E39C59E5AC77C45404B73F00D995
        56FFFFFE501F187B2C04FF00FFB24701F8CEA5FFFFFFFED1A5F4A45AEB994EE2
        8A3CD9792ACC6310C14F01D07931FFFFFFEAAF73893103FF00FFFF00FFC96518
        E0873BFEE5CBFFFFFFFAD5B1EDA563E28B3FD97B2CD4782AE1A46CFFFFFFF3CC
        A4AC4402893103FF00FFFF00FFFF00FFB64C04DE873BF8CEA3FFFAF3FFFFFFFE
        F6EEFCF3EAFFFFFFFEF7EEE6A56AAC44035A2214FF00FFFF00FFFF00FFFF00FF
        FF00FFC56418AF4501DC8840E9A76CEEBB89EBB581DC914DBD590F752D0C9034
        02FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFA646088B350575
        2D0C752D0C8B35059E4006FF00FFFF00FFFF00FFFF00FFFF00FF}
      OnClick = btnNextClick
      OnMouseLeave = btnNextClick
    end
    object btnStop: TSpeedButton
      Left = 128
      Top = 10
      Width = 25
      Height = 25
      GroupIndex = 1
      Down = True
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000120B0000120B00000000000000000000FF00FFFF00FF
        FF00FFFF00FFFF00FF7D2C057D2C057D2C057D2C057D2C057D2C05FF00FFFF00
        FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF552117552117BF5C15E19855EF
        BD8AF0BF8CE29D5BC26218541F16541F16FF00FFFF00FFFF00FFFF00FFFF00FF
        6C290EAF4704EBB179FFFEF8FEF8F4F2DAC4F2D9C2FCF6F0FFFFFCEEBA87B64E
        07602311FF00FFFF00FFFF00FF732D0DB04602F4D0ABFFFFFED48846BC4B02B8
        4300B84300BB4901D17F3BFCFAF4F8DDBDB64D05541F16FF00FFFF00FF732D0D
        E6AB72FFFFFFCC7228CA6B23D89151C56012C45C0DD89152CB6E28C7661DFCF8
        F4EFBC88541F16FF00FFB04A06C05C11FFFCFAE1A36ABF4800FFFFFFFFFFFFD4
        8742CF7930FFFFFFFFFFFFB53900D58945FFFFFFC160167B2C04B04A06DD9554
        FFFFFFD37628CC600EFFFFFFFFFFFFD98E49D37F36FFFFFFFFFFFFB84100C053
        05FCF8F3E29D5A7B2C04B04A06EBBB8AFBF0E7D87A2BD77422FFFFFFFFFFFFDE
        9655D98942FFFFFFFFFFFFBA4400BB4600F2DAC2EFC08E7B2C04B04A06EEBF90
        FCF4EBE28A3EE18435FFFFFFFFFFFFE29E5FDD914DFFFFFFFFFFFFBA4400BB47
        00F3DEC7EFBD8A7B2C04B04A06E9AA6EFFFFFFEDA462EA9547FFFFFFFFFFFFE6
        A569E19856FFFFFFFFFFFFB84200C15506FEFBF8E097527B2C04B04A06DD893F
        FFFCF8FAD7B4F4A359FFFFFFFFFFFFEAAB72E59E5EFFFFFFFFFFFFB63C00D995
        56FFFFFEBD5A107B2C04FF00FFB24701F8CEA5FFFFFFFED0A3F7B77BF2B780E5
        934CDD8438DE9350CE6E21CF782FFFFFFFEAAF73501F18FF00FFFF00FFB24701
        E0873BFEE5CBFFFFFFFAD3ADEDA05AE1893CD9792AD17021E09F64FFFFFFF3CC
        A4AC4402501F18FF00FFFF00FFFF00FFB64C04DE873BF8CEA3FFFAF3FFFFFFFE
        F6EEFCF3EAFFFFFFFEF7EEE6A56AAC44035A2214FF00FFFF00FFFF00FFFF00FF
        FF00FFAF4501AF4501DC8840E9A76CEEBB89EBB581DC914DBD590F5D23155D23
        15FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFA64608A64608A6
        4608A64608A64608A64608FF00FFFF00FFFF00FFFF00FFFF00FF}
      OnClick = btnStopClick
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 41
    Width = 745
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
      end>
    ExplicitLeft = -255
    ExplicitWidth = 1000
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 24
    Top = 72
  end
end