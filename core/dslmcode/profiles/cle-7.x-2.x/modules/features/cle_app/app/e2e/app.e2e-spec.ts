import { CleAppPage } from './app.po';

describe('cle-app App', function() {
  let page: CleAppPage;

  beforeEach(() => {
    page = new CleAppPage();
  });

  it('should display message saying app works', () => {
    page.navigateTo();
    expect(page.getParagraphText()).toEqual('app works!');
  });
});
